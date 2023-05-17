/***********************************************************************
 * File: backend.cpp
 * Author: 廖廷安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩, 廖廷安, 譚秉家 
 * Update Date: 2023/05/17
 * Description: Backend main program
***********************************************************************/
#include "backend.h"
#include "Json.h"

// this is the main function of the program
int main()
{
	gameServer = new WebSocketServer();
	thread timer_thread(gameMain);

	// the program will stock when run() is called , so thread is needed to run the loop
	gameServer->run(PORT);

	timer_thread.join(); // don't really know why this is needed
	return 0;
}
// this is the main function of the game
void gameMain() {
	Player* currentPlayer = NULL;
	while (true) {
		if (!gameServer->isConnected())
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		string command;
		while (*gameServer >> command)
		{
			json j = stringToJson(command);
			if (j == nullptr)
			{
				gameServer->send("Invalid json format... Try again.");
				cout << "Invalid json format... Try again." << endl;
				continue;
			}
			if (j["type"] == "init")
			{
				RunChessGame();
			}
		}
	}
}

void RunChessGame()
{

	Player* currentPlayer = NULL;
	// initialize a chess game and display the initial state
	Game::initialize();
	Board::getBoard()->display(cout);
	string fromSquare = "", toSquare = "";
	currentPlayer = Game::getNextPlayer();
	// game loop in which players alternate making moves
	while (true)
	{
		cout << currentPlayer->getName() << " player enter move (e.g. a2 a4): ";
		while (!gameServer->hasMessage())
		{
			// wait for message
		}
		string command = gameServer->getMessage();
		json j = stringToJson(command);
		if (j == nullptr)
		{
			gameServer->send("Invalid json format... Try again.");
			cout << "Invalid json format... Try again." << endl;
		}
		if (j["type"] == "click")
		{
			if (clickEvent(j, currentPlayer))
				currentPlayer = Game::getNextPlayer();
		}
		else if (j["type"] == "surrender")
		{
			surrenderEvent(j, currentPlayer);
			break;
		}
		else if (j["type"] == "exit")
		{
			break;
		}
		else
		{
			continue;
		}
		bool validMove = isValidMove(currentPlayer);

		if (!validMove)
		{
			if (currentPlayer->inCheck())
			{
				json message = { {"type","win"},{"player",Game::getNextPlayer()->getName()},{"success",true} };
				gameServer->send(message.dump());
				cout << Game::getNextPlayer()->getName() << " player wins." << endl;
				break;
			}
			else
			{
				json message = { {"type","draw"},{"player",currentPlayer->getName()} };
				gameServer->send(message.dump());
				cout << "Draw." << endl;
				break;
			}
		}
	}
}

bool clickEvent(json j, Player* currentPlayer)
{
	static string fromSquare = "", toSquare = "";
	string position = j["position"];
	if (!Board::getBoard()->squareAt(position[0] - 'a', position[1] - '1')->occupied())
	{
		if (fromSquare == "")
		{
			return false;
		}
		else
		{
			toSquare = position;
		}
	}
	else if (Board::getBoard()->squareAt(position[0] - 'a', position[1] - '1')->occupiedBy()->isWhite() == currentPlayer->isWhite())
	{
		fromSquare = position;
		json message = { {"success",true},{"type","firstClick"},{"position",fromSquare} };
		gameServer->send(message.dump());
		sendValidMoves (fromSquare, currentPlayer);

	}
	else if (fromSquare != "")
	{
		toSquare = position;
	}
	if (fromSquare == "" || toSquare == "")
		return false;
	if (currentPlayer->makeMove(fromSquare, toSquare))
	{
		json movemessage = { {"type","move"},{"from",fromSquare},{"to",toSquare} };
		gameServer->send(movemessage.dump());
		fromSquare = "";
		toSquare = "";
	}
	else
	{
		toSquare = "";
		return false;
	}
	Board::getBoard()->display(cout);
	return true;
}

void surrenderEvent(json j, Player* currentPlayer)
{
	json message = { {"type","surrender"},{"player",currentPlayer->getName()} };
	gameServer->send(message.dump());
	cout << currentPlayer->getName() << " player surrender." << endl;
}

void sendValidMoves(string fromSquare, Player* currentPlayer)
{
	json validMoves;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			if (Board::getBoard()->squareAt(fromSquare[0] - 'a', fromSquare[1] - '1')->occupiedBy()->hasMove(*currentPlayer, *(Board::getBoard()->squareAt(i, j))))
			{
				validMoves.push_back({ { "x",i },{ "y",j } });
			}
		}
	}
	json message = { {"success",true},{"type","validMoves"},{"validMoves",validMoves} };
	gameServer->send(message.dump());
}

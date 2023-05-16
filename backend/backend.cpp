/***********************************************************************
 * File: backend.cpp
 * Author: 廖廷安
 * Create Date: 2023/05/10
 * Editor:
 * Update Date: 2023/05/15
 * Description:
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
				RunChessGame();
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
			continue;
		}
		if (j["type"] == "click")
		{
			clickEvent(j, currentPlayer);
			continue;
		}
		else if (j["type"] == "surrender")
		{
			surrenderEvent(j, currentPlayer);
			break;
		}
		else
		{
			continue;
		}
	}
}

void clickEvent(json j, Player* currentPlayer)
{
	static string fromSquare = "", toSquare = "";
	if (fromSquare == "")
		fromSquare = j["position"];
	else if (toSquare == "")
		toSquare = j["position"];
	else
	{
		fromSquare = toSquare;
		toSquare = j["position"];
	}


	if (toSquare == "" || fromSquare == "")
	{
		gameServer->send("Invalid move... Try again.");
		cout << "Invalid move... Try again." << endl;
		return;
	}
	if (currentPlayer->makeMove(fromSquare, toSquare))
	{
		currentPlayer = Game::getNextPlayer();
		string movemessage = R"({"type":"move","from":")" + fromSquare + R"(","to":")" + toSquare + R"("})";
		gameServer->send(movemessage);
		fromSquare = "";
		toSquare = "";

	}
	else
	{
		cerr << "Invalid move... Try again." << endl;
		return;
	}
	Board::getBoard()->display(cout);

}

void surrenderEvent(json j, Player* currentPlayer)
{
	string message = R"({"type":"surrender","player":")" + currentPlayer->getName() + R"("})";
	gameServer->send(message);
	cout << currentPlayer->getName() << " player surrender." << endl;
}


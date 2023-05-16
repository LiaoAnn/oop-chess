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
		else
		{
			continue;
		}
		bool validMove = isValidMove(currentPlayer);
		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board::getBoard()->squareAt(i, j)->occupied())
				{
					for (int x = 0; x < 8; x++)
					{
						for (int y = 0; y < 8; y++)
						{
							if (Board::getBoard()->squareAt(i, j)->occupiedBy()->hasMove(*currentPlayer, *(Board::getBoard()->squareAt(x, y))))
							{
								cout << "valid move" << i << j << x << y << endl;
								validMove = true;
								break;
							}
							if (validMove)
								break;
						}
						if (validMove)
							break;
					}
				}
				if (validMove)
					break;
			}
			if (validMove)
				break;
		}*/

		if (!validMove)
		{
			if (currentPlayer->inCheck())
			{
				json message = { {"type","checkmate"},{"player",currentPlayer->getName()} };
				//string message = R"({"type":"checkmate","player":")" + currentPlayer->getName() + R"("})";

				gameServer->send(message.dump());
				cout << Game::getNextPlayer()->getName() << " player wins." << endl;
				break;
			}
			else
			{
				json message = { {"type","draw"},{"player",currentPlayer->getName()} };
				//string message = R"({"type":"draw","player":")" + currentPlayer->getName() + R"("})";

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
	if (fromSquare == "")
		fromSquare = j["position"];
	else if (toSquare == "")
		toSquare = j["position"];
	else
	{
		fromSquare = toSquare;
		toSquare = j["position"];
	}

	json message;
	if (toSquare == "" || fromSquare == "")
	{
		if (fromSquare != "")
			message = { {"success",true},{"type","firstClick"},{"position",fromSquare} };
		else
			message = { {"success",true},{"type","secondClick"},{"position",toSquare} };

		gameServer->send(message.dump());
		cout << message.dump() << endl;
		/*gameServer->send("Invalid move... Try again.");
		cout << "Invalid move... Try again." << endl;*/
		return false;
	}

	if (currentPlayer->makeMove(fromSquare, toSquare))
	{
		json movemessage = { {"type","move"},{"from",fromSquare},{"to",toSquare} };
		//string movemessage = R"({"type":"move","from":")" + fromSquare + R"(","to":")" + toSquare + R"("})";
		gameServer->send(movemessage.dump());
		fromSquare = "";
		toSquare = "";
	}
	else
	{
		cerr << "Invalid move... Try again." << endl;
		return false;
	}

	Board::getBoard()->display(cout);
	return true;
}

void surrenderEvent(json j, Player* currentPlayer)
{
	json message = { {"type","surrender"},{"player",currentPlayer->getName()} };
	//string message = R"({"type":"surrender","player":")" + currentPlayer->getName() + R"("})";
	gameServer->send(message.dump());
	cout << currentPlayer->getName() << " player surrender." << endl;
}


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

int main()
{
	WebSocketServer server;

	global = &server; // set global pointer to server
	thread timer_thread(loop);
	RunChessGame();

	// the program will stock when run() is called , so thread is needed to run the loop
	server.run(PORT);

	timer_thread.join(); // don't really know why this is needed
	return 0;
}

void loop() {
	Player* currentPlayer = NULL;

	while (true) {
		if (!global->isConnected())
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}

		string command;
		while (*global >> command)
		{
			currentPlayer = Game::getNextPlayer();
			json j = stringToJson(command);

			// if json format is wrong
			if (j == nullptr)
			{
				global->send("Invalid json format... Try again.");
				continue;
			}

		}
		//===================================WARNING===============================
		//for release version don't put any thing here unless you want to slow down the program or really no other choice
		//=========================================================================
	}
}


/**
 * Main program for playing a chess game.
 */
void RunChessGame()
{
	string fromSquare = "  ", toSquare = "  ";
	Player* currentPlayer = NULL;

	// initialize a chess game and display the initial state
	Game::initialize();
	//Board::getBoard()->display(cout);

	// game loop in which players alternate making moves
	/*while (true)
	{
		currentPlayer = Game::getNextPlayer();

		cout << currentPlayer->getName() << " player enter move (e.g. a2 a4): ";
		cin >> fromSquare >> toSquare;

		while (!currentPlayer->makeMove(fromSquare, toSquare))
		{
			cerr << "Invalid move... Try again." << endl;
			cin >> fromSquare >> toSquare;
		}
		Board::getBoard()->display(cout);
	}*/
}



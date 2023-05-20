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

/**
 * Intent: main function
 * Pre: no variable required
 * Post: return 0 if the program runs no problem till the end
 */
int main()
{
	// create the data transfer server
	gameServer = new WebSocketServer();
	// create a thread to run the game
	thread timer_thread(gameMain);
	// run the data transfer server
	gameServer->run(PORT);
	//run the game
	timer_thread.join();
	return 0;
}

/**
 * Intent: main function of the game
 * Pre: no variable required
 * Post: no return value
 */
void gameMain() {
	//Player* currentPlayer = NULL;
	// game start loop
	while (true)
	{
		// wait for connection
		if (!gameServer->isConnected())
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		string command;
		// wait for init command from client, should filter out possibl error command
		while (*gameServer >> command)
		{
			// convert string to json
			json j = stringToJson(command);
			if (j == nullptr)
			{
				gameServer->send("Invalid json format... Try again.");
				cout << "Invalid json format... Try again." << endl;
				continue;
			}
			// iff the command is init, start the game
			if (j["type"] == "init")
			{
				runChessGame();
			}
		}
	}
}

/**
 * Intent: initialize a chess game and display the initial state
 * Pre: no variable required
 * Post: no return value
 */
void runChessGame()
{
	Player* currentPlayer = NULL;
	// initialize a chess game and display the initial state
	Game::initialize();
	// display the initial state
	Board::getBoard()->display(cout);
	// date buffer
	string fromSquare = "", toSquare = "";
	// get the first player (0+1)
	currentPlayer = Game::getNextPlayer();
	// game loop in which players alternate making moves
	while (true)
	{
		cout << currentPlayer->getName() << " player enter move (e.g. a2 a4): ";
		while (!gameServer->hasMessage())
		{
			// wait for message
		}
		// get the message
		string command = gameServer->getMessage();
		json j = stringToJson(command);
		if (j == nullptr)
		{
			gameServer->send("Invalid json format... Try again.");
			cout << "Invalid json format... Try again." << endl;
			continue;
		}
		// event switch (but use if else for more readable)
		if (j["type"] == "click")
		{
			// if the click event is valid, change the current player
			if (clickEvent(j, currentPlayer))
				currentPlayer = Game::getNextPlayer();
		}
		else if (j["type"] == "surrender")
		{
			// surrender and end the game
			surrenderEvent(j, currentPlayer);
			break;
		}
		else if (j["type"] == "exit")
		{
			// for disconnecting event of web client
			break;
		}
		else
		{
			// invalid event
			cout << "Invalid event... Try again." << endl;
			continue;
		}

		// check if the current player has any single valid move
		bool validToMove = isValidMove(currentPlayer);

		// if the current player has no valid move, check if the current player is in check
		if (!validToMove)
		{
			// if the current player is in check, the current player loses
			if (currentPlayer->inCheck())
			{
				json message = { {"type","win"},{"player",Game::getNextPlayer()->getName()},{"success",true} };
				gameServer->send(message.dump());
				cout << Game::getNextPlayer()->getName() << " player wins." << endl;
			}
			// if the current player is not in check, the game is a draw
			else
			{
				json message = { {"type","draw"},{"player",currentPlayer->getName()} };
				gameServer->send(message.dump());
				cout << "Draw." << endl;
			}
			// end the game
			break;
		}
	}
}

/**
 * Intent: user click event
 * Pre: j is a json object, currentPlayer is a pointer to the current player
 * Post: return true if the click event is valid, false otherwise
 */
bool clickEvent(json j, Player* currentPlayer)
{
	int beforevalue; // to check if pawn is promoted
	static string fromSquare = "", toSquare = ""; // use static to keep the value in different function calls
	// get the position of the click
	string position = j["position"];
	// click on an empty square
	if (!Board::getBoard()->squareAt(position[0] - 'a', position[1] - '1')->occupied())
	{
		// if the fromSquare is empty, return false
		if (fromSquare == "")
			return false;
		// if the fromSquare is not empty, set the toSquare
		else
			toSquare = position;
	}
	// click on a square occupied by the own players piece
	else if (Board::getBoard()->squareAt(position[0] - 'a', position[1] - '1')->occupiedBy()->isWhite() == currentPlayer->isWhite())
	{
		// set the fromSquare to the new position (piece)
		fromSquare = position;
		// send the valid first click message
		json message = { {"success",true},{"type","firstClick"},{"position",fromSquare} };
		gameServer->send(message.dump());
		// send all the valid moves
		sendValidMoves(fromSquare, currentPlayer);

	}
	// click on a square occupied by the opponent players piece
	else if (fromSquare != "")
	{
		toSquare = position;
	}
	// if the fromSquare and toSquare are both valid, try make the move
	if (fromSquare == "" || toSquare == "")
		return false;
	bool takepiece = false; // to check to take piece
	if (Board::getBoard()->squareAt(toSquare[0] - 'a', toSquare[1] - '1')->occupied()) // if the toSquare is occupied
		takepiece = true;
	beforevalue = Board::getBoard()->squareAt(fromSquare[0] - 'a', fromSquare[1] - '1')->occupiedBy()->value(); // stash the value of the piece before move
	if (currentPlayer->makeMove(fromSquare, toSquare))
	{
		//pawn passant take
		if (Board::getBoard()->squareAt(toSquare[0] - 'a', toSquare[1] - '1')->occupiedBy()->value() == 1 && fromSquare[0] != toSquare[0] && !takepiece)
		{
			// takeout is the position of the piece that is taken
			string takeout = { toSquare[0],fromSquare[1] };
			json takemessage = { {"type","take"},{"takeout",takeout} };
			gameServer->send(takemessage.dump());
		}
		// normal take
		json takemessage = { {"type","take"},{"takeout",toSquare} };
		if (takepiece)
			gameServer->send(takemessage.dump());
		// move
		json movemessage = { {"type","move"},{"from",fromSquare},{"to",toSquare} };
		gameServer->send(movemessage.dump());
		// promotion
		if (beforevalue == 1 && Board::getBoard()->squareAt(toSquare[0] - 'a', toSquare[1] - '1')->occupiedBy()->value() != 1)
		{
			json promotionmessage = { {"type","promotion"},{"position",toSquare} };
			gameServer->send(promotionmessage.dump());
		}
		// sign the last move piece
		if (Game::lastMovePiece)
			Game::lastMovePiece->setLastMove(false);
		Game::lastMovePiece = Board::getBoard()->squareAt(toSquare[0] - 'a', toSquare[1] - '1')->occupiedBy();
		Game::lastMovePiece->setLastMove(true);
		// all process done, reset the fromSquare and toSquare
		fromSquare = "";
		toSquare = "";
	}
	else
	{
		// if the move is invalid, reset the toSquare
		toSquare = "";
		cout << "Invalid move." << endl;
		return false;
	}
	// display the board (on the backend server side)
	Board::getBoard()->display(cout);
	return true;
}

/**
 * Intent: user surrender event, when user click the surrender button
 * Pre: j is a json object, currentPlayer is a pointer to the current player
 * Post:
 */
void surrenderEvent(json j, Player* currentPlayer)
{
	// just send the surrender message
	json message = { {"type","surrender"},{"player",currentPlayer->getName()} };
	gameServer->send(message.dump());
	cout << currentPlayer->getName() << " player surrender." << endl;
}

/**
 * Intent: send the valid moves of a piece to the client
 * Pre: fromSquare currentPlayer is a pointer to the current player
 * Post: send the valid moves of a piece to the client using json format
 */
void sendValidMoves(string fromSquare, Player* currentPlayer)
{
	json validMoves;
	// check all the squares on the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) 
		{
			if (Board::getBoard()->squareAt(fromSquare[0] - 'a', fromSquare[1] - '1')->occupiedBy()->hasMove(*currentPlayer, *(Board::getBoard()->squareAt(i, j))))
			{
				// if the move is valid, add the move to the validMoves
				validMoves.push_back({ { "x",i },{ "y",j } });
			}
		}
	}
	// send the validMoves to the client, if the validMoves is empty, validMoves will be NULL
	json message = { {"success",true},{"type","validMoves"},{"validMoves",validMoves} };
	gameServer->send(message.dump());
}

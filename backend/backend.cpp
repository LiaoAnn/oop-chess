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
	// open the web page
	// create the data transfer server
	gameServer = new WebSocketServer();
	webServer = new WebServer(WEBROOT, WEBPORT);
	// create a thread to run the game
	thread web_thread(web_page);
	thread timer_thread(gameMain);
	thread web(webServerThread);
	// run the data transfer server
	gameServer->run(PORT);
	//run the game
	web_thread.join();
	timer_thread.join();
	web.join();

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
			this_thread::sleep_for(std::chrono::milliseconds(100));
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
		cout << currentPlayer->getName() << " player enter move :";
		while (!gameServer->hasMessage())
		{
			// wait for message
		}
		// get the message
		string command = gameServer->getMessage();
		json j = stringToJson(command);
		if (j == nullptr)
		{
			cout << "Invalid json format" << endl;
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
// Intent: get the content type of a file
// Pre: fileExtension is a string reference
// Post: return the content type of the file
std::string getContentType(const std::string& fileExtension) {
	if (fileExtension == "html" || fileExtension == "htm")
		return "text/html";
	else if (fileExtension == "css")
		return "text/css";
	else if (fileExtension == "js")
		return "text/javascript";
	else if (fileExtension == "jpg" || fileExtension == "jpeg")
		return "image/jpeg";
	else if (fileExtension == "png")
		return "image/png";
	else if (fileExtension == "gif")
		return "image/gif";
	else if (fileExtension == "ico")
		return "image/x-icon";
	else
		return "application/octet-stream";
}
// Intent: static file server
// Pre: file is a string reference
// Post: send the file to the client
int web_page() {
	namespace asio = boost::asio;
	using tcp = boost::asio::ip::tcp;
	namespace fs = boost::filesystem;
	// Set the IP address and port number for the server
	const std::string address = "127.0.0.1";
	const unsigned short port = 5173;

	try {
		// Create the I/O context and TCP acceptor
		asio::io_context io_context;
		tcp::acceptor acceptor(io_context, { tcp::v4(), port });

		while (true) {
			// Wait for incoming connection
			tcp::socket socket(io_context);
			acceptor.accept(socket);
			// Read the request
			asio::streambuf request_buffer;
			asio::read_until(socket, request_buffer, "\r\n\r\n");

			// Extract the requested file path
			std::string request_str(asio::buffers_begin(request_buffer.data()), asio::buffers_end(request_buffer.data()));
			std::string request_path;
			size_t path_start = request_str.find("GET") + 4;
			size_t path_end = request_str.find("HTTP") - 1;
			if (path_start != std::string::npos && path_end != std::string::npos) {
				request_path = request_str.substr(path_start, path_end - path_start);
			}

			// Trim leading and trailing whitespace and remove potential URL query parameters
			request_path = fs::path(request_path).lexically_normal().string();

			// Check if the requested file exists
			if (request_path == "\\")
				request_path = "\\index.html";
			fs::path file_path("dist" + request_path);
			string content_type = getContentType(file_path.extension().string().substr(1));
			if (fs::exists(file_path) && fs::is_regular_file(file_path)) {
				// Open the file			
				cout << file_path.string() << endl;
				std::ifstream file(file_path.string(), std::ios::binary);
				if (file) {
					// Read the file content
					std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

					// Send the response headers
					std::ostringstream response_stream;
					response_stream << "HTTP/1.1 200 OK\r\n";
					response_stream << "Content-Type: " << content_type << "\r\n";
					//response_stream << "Content-Type: text/html\r\n";
					response_stream << "Content-Length: " << content.length() << "\r\n";
					response_stream << "Connection: close\r\n\r\n";
					std::string response_headers = response_stream.str();

					// Send the response headers and file content
					asio::write(socket, asio::buffer(response_headers));
					asio::write(socket, asio::buffer(content));
				}
			}
			else {
				// Send a 404 Not Found response
				std::string not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
				asio::write(socket, asio::buffer(not_found_response));
			}

			// Close the socket
			socket.shutdown(tcp::socket::shutdown_both);
			socket.close();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void webServerThread()
{
	system("start http://localhost");
	webServer->run();
}

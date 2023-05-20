/***********************************************************************
 * File: WebSocketServer.cpp
 * Author: 劉耀恩
 * Create Date: 2023/05/15
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of WebSocketServer class
***********************************************************************/
#include "WebSocketServer.h"
#include <istream>
#include "Json.h"
// Intent: WebSocketServer constructor
// Pre: no variable required
// Post: WebSocketServer object created
WebSocketServer::WebSocketServer()
{
	// set logging settings (all except message payloads)
	mServer.set_access_channels(websocketpp::log::alevel::all); 
	mServer.clear_access_channels(websocketpp::log::alevel::frame_header);
	mServer.clear_access_channels(websocketpp::log::alevel::frame_payload);
	// Initialize Asio
	mServer.init_asio();
	// Register our message handler
	mServer.set_message_handler(bind(&WebSocketServer::onMessage, this, ::_1, ::_2));
	mServer.set_open_handler(bind(&WebSocketServer::onOpen, this, ::_1));
	mServer.set_close_handler(bind(&WebSocketServer::onClose, this, ::_1));
}
// Intent: Open a port and listen to it. 
// Pre: port number is a 16-bit unsigned integer
// Post: WebSocketServer object created
//NOTICE: this is not websocketpp::server<websocketpp::config::asio>  run() function ifself
void WebSocketServer::run(uint16_t port)
{
	// listen to port
	mServer.listen(port);
	cout << "Server listening on port " << port << endl;
	// Start the server accept loop
	mServer.start_accept();
	// Start the ASIO io_service run loop
	mServer.run();
}
// Intent: on message received event 
// Pre: hdl is a websocketpp::connection_hdl object and msg is a websocketpp::server::message_ptr object
// Post: no return 
void WebSocketServer::onMessage(websocketpp::connection_hdl hdl, message_ptr msg)
{
	// get and store message
	std::string str = msg->get_payload();
	messageQueue.push_back(str);
}
// Intent: on connection established event
// Pre: hdl is a websocketpp::connection_hdl object
// Post: no return
void WebSocketServer::onOpen(websocketpp::connection_hdl hdl)
{
	// link client connection pointer to the connection
	client = mServer.get_con_from_hdl(hdl);
	connected = true;
}
void WebSocketServer::onClose(websocketpp::connection_hdl hdl)
{
	// clear client connection pointer
	client = nullptr;
	connected = false;
	// push a disconnect message to the message queue
	json disconnectMessage = { {"type", "exit"} };
	messageQueue.push_back(disconnectMessage.dump());
}
// Intent: stop the server
// Pre: no variable required
// Post: server stopped
void WebSocketServer::stop()
{
	mServer.stop();
}
// Intent: send a string to the client
// Pre: str is a string
// Post: return true if the message is sent, false otherwise
// NOTICE: return true does not mean the message is received by the client, it only means the message sent successfully
bool WebSocketServer::send(std::string str)
{
	if (isConnected())
		mServer.send(client->get_handle(), str, websocketpp::frame::opcode::text);
	else
		return false;
	return true;
}
// Intent: send an integer to the client
// Pre: i is an integer
// Post: return true if the message is sent, false otherwise
// NOTICE: return true does not mean the message is received by the client, it only means the message sent successfully
bool WebSocketServer::send(int i)
{
	if (isConnected())
		mServer.send(client->get_handle(), reinterpret_cast<const char*>(&i), sizeof(i), websocketpp::frame::opcode::binary);
	else
		return false;
	return true;
}
// Intent: read a string from the message queue
// Pre: variable is a string
// Post: return true if there is a message in the queue, false otherwise
bool WebSocketServer::operator >>(std::string& variable)
{
	if (hasMessage())
		variable = getMessage();
	else
		return false;
	return true;
}

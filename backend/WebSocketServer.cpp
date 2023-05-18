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
	mServer.set_access_channels(websocketpp::log::alevel::all);
	mServer.clear_access_channels(websocketpp::log::alevel::frame_payload);
	mServer.init_asio();
	mServer.set_message_handler(bind(&WebSocketServer::onMessage, this, ::_1, ::_2));
	mServer.set_open_handler(bind(&WebSocketServer::onOpen, this, ::_1));
	mServer.set_close_handler(bind(&WebSocketServer::onClose, this, ::_1));
	// disable on_message logging
	mServer.clear_access_channels(websocketpp::log::alevel::frame_header);
	mServer.clear_access_channels(websocketpp::log::alevel::frame_payload);
}
// Intent: Open a port and listen to it
// Pre: port number is a 16-bit unsigned integer
// Post: WebSocketServer object created
void WebSocketServer::run(uint16_t port)
{
	mServer.listen(port);
	cout << "Server listening on port " << port << endl;
	mServer.start_accept();
	mServer.run();
}
// Intent: on message received event 
// Pre: hdl is a websocketpp::connection_hdl object and msg is a websocketpp::server::message_ptr object
// Post: no return 
void WebSocketServer::onMessage(websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::string str = msg->get_payload();
	messageQueue.push_back(str);
	//m_server.send(hdl, "Server received: " + msg->get_payload(), msg->get_opcode());
}
// Intent: on connection established event
// Pre: hdl is a websocketpp::connection_hdl object
// Post: no return
void WebSocketServer::onOpen(websocketpp::connection_hdl hdl)
{
	client = mServer.get_con_from_hdl(hdl);
	connected = true;
}
void WebSocketServer::onClose(websocketpp::connection_hdl hdl)
{
	client = nullptr;
	connected = false;
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
// Post: no return
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
// Post: no return
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

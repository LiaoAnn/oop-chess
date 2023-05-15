/***********************************************************************
 * File: WebSocketServer.cpp
 * Author: ¼BÄ£®¦
 * Create Date: 2023/05/15
 * Editor: ¼BÄ£®¦
 * Update Date: 2023/05/15
 * Description:
***********************************************************************/
#include "WebSocketServer.h"
#include <istream>
// Intent: WebSocketServer constructor
// Pre: no variable required
// Post: WebSocketServer object created
WebSocketServer::WebSocketServer()
{
	m_server.set_access_channels(websocketpp::log::alevel::all);
	m_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	m_server.init_asio();
	m_server.set_message_handler(bind(&WebSocketServer::on_message, this, ::_1, ::_2));
	m_server.set_open_handler(bind(&WebSocketServer::on_open, this, ::_1));
	m_server.set_close_handler(bind(&WebSocketServer::on_close, this, ::_1));
	// disable on_message logging
	m_server.clear_access_channels(websocketpp::log::alevel::frame_header);
	m_server.clear_access_channels(websocketpp::log::alevel::frame_payload); 	
}
// Intent: Open a port and listen to it
// Pre: port number is a 16-bit unsigned integer
// Post: WebSocketServer object created
void WebSocketServer::run(uint16_t port)
{
	m_server.listen(port);
	m_server.start_accept();
	m_server.run();
}
// Intent: on message received event 
// Pre: hdl is a websocketpp::connection_hdl object and msg is a websocketpp::server::message_ptr object
// Post: no return 
void WebSocketServer::on_message(websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::string strr = msg->get_payload();
	//std::cout << "\n\n\n" << strr << "\n\n\n" << std::endl;
	messageQueue.push_back(strr);
	std::string str = "Server received: " + msg->get_payload();
	m_server.send(hdl, str, msg->get_opcode());
}
// Intent: on connection established event
// Pre: hdl is a websocketpp::connection_hdl object
// Post: no return
void WebSocketServer::on_open(websocketpp::connection_hdl hdl)
{
	std::string str = "Server connected! Welcome";
	m_server.send(hdl, str, websocketpp::frame::opcode::text);
	client = m_server.get_con_from_hdl(hdl);
	connected = true;
}
void WebSocketServer::on_close(websocketpp::connection_hdl hdl)
{
	client = nullptr;
	connected = false;
}
// Intent: stop the server
// Pre: no variable required
// Post: server stopped
void WebSocketServer::stop()
{
	m_server.stop();
}
// Intent: send a string to the client
// Pre: str is a string
// Post: no return
bool WebSocketServer::send(std::string str)
{
	if (isConnected())
		m_server.send(client->get_handle(), str, websocketpp::frame::opcode::text);
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
		m_server.send(client->get_handle(), reinterpret_cast<const char*>(&i), sizeof(i), websocketpp::frame::opcode::binary);
	else
		return false;
	return true;
}

bool WebSocketServer::operator >>(std::string& variable)
{
	if (hasMessage())
		variable = getMessage();
	else
		return false;
	return true;
}

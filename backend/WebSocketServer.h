/***********************************************************************
 * File: WebSocketServer.h
 * Author: �Bģ��
 * Create Date: 2023/05/15
 * Editor: �Bģ��
 * Update Date: 2023/05/15
 * Description:
***********************************************************************/
#pragma once
#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <istream>
#include <vector>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1; // set up placeholders for callbacks
using websocketpp::lib::placeholders::_2; // set up placeholders for callbacks
using websocketpp::lib::bind; // set up placeholders for callbacks
using namespace std;

typedef server::message_ptr message_ptr;

class WebSocketServer {
public:
	WebSocketServer();
	void run(uint16_t port); // run the server on port
	void stop(); // actually useless haha
	bool send(std::string str);
	bool send(int i);
	bool isConnected() { return connected; }
	bool hasMessage() { return messageQueue.size() > 0; }
	std::string getMessage() { std::string str = messageQueue[0]; messageQueue.erase(messageQueue.begin()); return str; }
	bool  operator>>(std::string&);
private:
	bool connected = false;
	server m_server;
	std::vector <std::string> messageQueue; // message queue
	server::connection_ptr client; // client connection pointer
	void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
	void on_open(websocketpp::connection_hdl hdl);
	void on_close(websocketpp::connection_hdl hdl);
};
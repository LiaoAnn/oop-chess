/***********************************************************************
 * File: WebServer.h
 * Author: 劉耀恩
 * Create Date: 2023/06/15
 * Editor: 劉耀恩
 * Update Date: 2023/06/15
 * Description: WebServer
 ************************************************************************/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;
namespace http = boost::beast::http;

class WebServer
{
public:
	WebServer(string root_directory, int port);
	void run();
private:
	string get_file_content(const  string& file_path);
	string get_content_type(const  string& file_path);
	void handle_request(const http::request<http::string_body>& request, http::response<http::string_body>& response);
	int port;
	string root_directory;
};


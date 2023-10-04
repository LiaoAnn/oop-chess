/***********************************************************************
 * File: backend.h
 * Author: 譚秉家
 * Create Date: 2023/05/15
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: backend
***********************************************************************/
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "WebSocketServer.h"
#include "WebServer.h"
#include "Game.h"
#include "Board.h"
#include "Json.h"
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

using namespace std;
WebSocketServer* gameServer;
const int PORT = 9002;
WebServer* webServer;
const int WEBPORT = 80;
const string WEBROOT = "dist";

// main function of the game
void gameMain();
// initialize a chess game and display the initial state
void runChessGame();
// send the valid moves of a piece to the client
void sendValidMoves(string, Player*);
// user click event
bool clickEvent(json, Player*);
// user surrender event, when user click the surrender button
void surrenderEvent(json, Player*);
// host static file server for client web page
int web_page();

void webServerThread();
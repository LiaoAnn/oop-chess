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
#include "game.h"
#include "board.h"
#include "Json.h"

using namespace std;
WebSocketServer* gameServer;
const int PORT = 9002;

void gameMain();
void RunChessGame();
void sendValidMoves(string, Player*);
bool clickEvent(json, Player*);
void surrenderEvent(json, Player*);

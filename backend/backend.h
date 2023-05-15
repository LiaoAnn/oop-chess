/***********************************************************************
 * File: backend.h
 * Author: BING-JIA TAN (B11115001)
 * Create Date: 2023-05-15
 * Editor: BING-JIA TAN (B11115001)
 * Update Date: 2023-05-15
 * Description: Describe here
************************************************************************/
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include "WebSocketServer.h"
#include "game.h"
#include "board.h"

using namespace std;
WebSocketServer* global;
const int PORT = 9002;

void loop();
void RunChessGame();

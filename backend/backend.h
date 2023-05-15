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

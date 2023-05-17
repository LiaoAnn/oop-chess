﻿/***********************************************************************
 * File: game.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: game class
***********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <set>
#include <iostream>
#include "board.h"
#include "piece.h"
#include "player.h"

using namespace std;

class Game
{
public:
	~Game();
	static void initialize();
	static Player* getNextPlayer();
	static Player* opponentOf(Player& player);

private:
	Game();
	static Player* player1;
	static Player* player2;
	static Player* nextPlayer;
	static set<Piece*> whitePieces;
	static set<Piece*> blackPieces;

};

bool isValidMove(Player*);
#endif

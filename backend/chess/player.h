/***********************************************************************
 * File: player.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: player class
***********************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "piece.h"
#include "King.h"

using namespace std;

class Player
{
public:
    Player(string name, bool isWhite, King& myKing, set<Piece*>& myPieces);
    ~Player();
    bool makeMove(string, string);
    bool inCheck();
    void capture(Piece* aPiece);
    string getName() const;
    bool isWhite() const;
    int score() const;
    set<Piece*>* getMyPieces() const;
    King* getMyKing() const;
private:
    // Private attributes
    string name;
    bool white;
    set<Piece*>& myPieces;
    set<Piece*> capturedPieces;
    King& myKing;
};

#endif

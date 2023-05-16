#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "piece.h"
#include "king.h"

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
}; // Player

#endif

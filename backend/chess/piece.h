/***********************************************************************
 * File: Piece.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: piece class
***********************************************************************/

#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include "Square.h"
#include "Board.h"
class Player;

using namespace std;

class Piece
{
public:
	Piece(bool isWhite);
	virtual ~Piece();
	virtual bool moveTo(Player& byPlayer, Square& toSquare);
	virtual bool hasMove(Player& byPlayer, Square& toSquare);
	virtual void setLocation(Square* location);
	virtual int value() const = 0;
	bool isWhite() const;
	string color() const;
	virtual void display() const = 0;
	virtual bool canMoveTo(Square& location) const = 0;
	bool isOnSquare() const;
	Square* location() const;
	int hasMoved();
	virtual void setLastMove(bool);
	virtual bool isLastMove();

protected:
	bool _isWhite;
	int _moved = 0;
	string _color;
	bool lastMove = false;

private:
	Square* _square;

};

#endif

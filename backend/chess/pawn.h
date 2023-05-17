/***********************************************************************
 * File: Pawn.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Pawn class
***********************************************************************/

#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "square.h"
#include "RestrictedPiece.h"

using namespace std;

class Pawn : public RestrictedPiece
{
public:
	Pawn(bool isWhite);
	~Pawn();
	void setLocation(Square* location);
	int value() const;
	bool moveTo(Player& byPlayer, Square& to);
	bool canMoveTo(Square& location) const;
	void display() const;

private:
	Piece* _delegate;

};

#endif

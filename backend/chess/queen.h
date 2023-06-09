/***********************************************************************
 * File: Queen.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Queen class
***********************************************************************/

#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include "Square.h"
#include "Piece.h"

using namespace std;

class Queen : public Piece
{
public:
	Queen(bool isWhite);
	~Queen();
	int value() const;
	bool canMoveTo(Square& location) const;
	void display() const;

};

#endif
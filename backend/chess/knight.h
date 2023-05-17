/***********************************************************************
 * File: Knight.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Knight class
***********************************************************************/

#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include "square.h"
#include "Piece.h"

using namespace std;

class Knight : public Piece
{
public:
	Knight(bool isWhite);
	~Knight();
	int value() const;
	bool canMoveTo(Square& location) const;
	void display() const;

};

#endif

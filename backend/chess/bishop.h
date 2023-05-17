/***********************************************************************
 * File: Bishop.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Bishop class
***********************************************************************/

#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include "Piece.h"
#include "square.h"

using namespace std;

// Bishop piece
class Bishop : public Piece
{
public:
	Bishop(bool isWhite);
	~Bishop();
	int value() const;
	bool canMoveTo(Square& location) const;
	void display() const;
};

#endif

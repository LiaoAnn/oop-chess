/***********************************************************************
 * File: RestrictedPiece.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of RestrictedPiece class
 ***********************************************************************/
#include "Player.h"
#include "RestrictedPiece.h"
 // Intent: constructor of RestrictedPiece
 // Pre: isWhite is a valid bool
 // Post: a RestrictedPiece is constructed
RestrictedPiece::RestrictedPiece(bool isWhite) : Piece(isWhite)
{
	_moved = 0;
}
// Intent: destructor of RestrictedPiece
// Pre: no variable required
// Post: a RestrictedPiece is destructed
RestrictedPiece::~RestrictedPiece()
{
}
// Intent: check if RestrictedPiece can move to the location
// Pre: location is a valid Square
// Post: return true if RestrictedPiece can move to the location, false otherwise
bool RestrictedPiece::moveTo(Player& byPlayer, Square& to)
{
	bool validMove = Piece::moveTo(byPlayer, to);

	// only change _moved if a valid move is made 
	// and this piece hasn't already been moved
	if (validMove)
	{
		_moved++;
	}

	return validMove;
}
// Intent: check if RestrictedPiece has moved
// Pre: no variable required
// Post: return true if RestrictedPiece has moved, false otherwise
int RestrictedPiece::hasMoved() const
{
	return _moved;
}


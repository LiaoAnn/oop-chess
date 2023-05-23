/***********************************************************************
 * File: Square.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Square class
***********************************************************************/
#include "Piece.h"
#include "Square.h"
// Intent: constructor of Square
// Pre: x and y are valid int
// Post: a Square is constructed
Square::Square(int x, int y) : _x(x), _y(y), _piece(NULL)
{
}
// Intent: destructor of Square
// Pre: no variable required
// Post: a Square is destructed
Square::~Square()
{
}
// Intent: set the occupier of Square
// Pre: piece is a valid Piece
// Post: the occupier of Square is set
void Square::setOccupier(Piece* piece)
{
	_piece = piece;
}
// Intent: get the x value of Square
// Pre: no variable required
// Post: return the x value of Square
int Square::getX() const
{
	return _x;
}
// Intent: get the y value of Square
// Pre: no variable required
// Post: return the y value of Square
int Square::getY() const
{
	return _y;
}
// Intent: check if Square is occupied
// Pre: no variable required
// Post: return true if Square is occupied, false otherwise
bool Square::occupied() const
{
	return _piece;
}
// Intent: get the occupier of Square
// Pre: no variable required
// Post: return the occupier of Square
Piece* Square::occupiedBy() const
{
	return _piece;
}
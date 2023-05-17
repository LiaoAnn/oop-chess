/***********************************************************************
 * File: king.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of King
***********************************************************************/
#include "king.h"
// Intent: constructor of King
// Pre: isWhite is a valid bool
// Post: a King is constructed
King::King(bool isWhite) : RestrictedPiece(isWhite)
{
}
// Intent: destructor of King
// Pre: no variable required
// Post: a King is destructed
King::~King()
{
}
// Intent: get the value of King
// Pre: no variable required
// Post: return the value of King
int King::value() const
{
    return 0;
}
// Intent: check if King can move to the location
// Pre: location is a valid Square
// Post: return true if King can move to the location, false otherwise
bool King::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    // valid move if moving 1 square forward/backwards
    if(abs(translationY) == 1 && translationX == 0)
    {
        validMove = true;
    }
    
    // valid move if moving 1 square sideways
    else if(abs(translationX) == 1 && translationY == 0)
    {
        validMove = true;
    }
    
    // valid move if moving 1 square diagonally
    else if(abs(translationX) == 1 && abs(translationY) == 1)
    {
        validMove = true;
    }
    
    return validMove;
}
// Intent: display the King
// Pre: no variable required
// Post: display the King
void King::display() const
{
    cout << _color + "K";
}
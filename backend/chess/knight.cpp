/***********************************************************************
 * File: knight.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Knight class
***********************************************************************/
#include "knight.h"

// Intent: constructor of Knight
// Pre: isWhite is a valid bool
// Post: a Knight is constructed
Knight::Knight(bool isWhite) : Piece(isWhite)
{
}
// Intent: destructor of Knight
// Pre: no variable required
// Post: a Knight is destructed
Knight::~Knight()
{
}
// Intent: get the value of Knight
// Pre: no variable required
// Post: return the value of Knight
int Knight::value() const
{
    return 3;
}
// Intent: check if Knight can move to the location
// Pre: location is a valid Square
// Post: return true if Knight can move to the location, false otherwise
bool Knight::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    // valid move if moving 1 square forward/backwards
    // and 2 squares sideways
    if(abs(translationY) == 1 && abs(translationX) == 2)
    {
        validMove = true;
    }
    
    // valid move if moving 1 square sideways and 2 squares
    // forward/backwards
    else if(abs(translationX) == 1 && abs(translationY) == 2)
    {
        validMove = true;
    }
    
    return validMove;
}
// Intent: display the Knight
// Pre: no variable required
// Post: display the Knight
void Knight::display() const
{
    cout << _color + "N";
}




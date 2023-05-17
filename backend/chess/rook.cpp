/***********************************************************************
 * File: Rook.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Rook class
***********************************************************************/
#include "Rook.h"
// Intent: constructor of Rook
// Pre: isWhite is a valid bool
// Post: a Rook is constructed
Rook::Rook(bool isWhite) : RestrictedPiece(isWhite)
{
}
// Intent: destructor of Rook
// Pre: no variable required
// Post: a Rook is destructed
Rook::~Rook()
{
}
// Intent: get the value of Rook
// Pre: no variable required
// Post: return the value of Rook
int Rook::value() const
{
    return 5;
}
// Intent: check if Rook can move to the location
// Pre: location is a valid Square
// Post: return true if Rook can move to the location, false otherwise
bool Rook::canMoveTo(Square& location) const
{
    bool validMove = false;
    
    // valid move if moving on a clear vertical
    if(Board::getBoard()->isClearVertical(*(this->location()), location))
    {
        validMove = true;
    }
    
    // valid move if moving on a clear horizontal
    else if(Board::getBoard()->isClearHorizontal(*(this->location()), location))
    {
        validMove = true;
    }
    
    return validMove;
}
// Intent: display the Rook
// Pre: no variable required
// Post: 
void Rook::display() const
{
    cout << _color + "R";
}
/***********************************************************************
 * File: queen.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Queen class
***********************************************************************/
#include "queen.h"
// Intent: constructor of Queen
// Pre: isWhite is a valid bool
// Post: a Queen is constructed
Queen::Queen(bool isWhite) : Piece(isWhite)
{
}
// Intent: destructor of Queen
// Pre: no variable required
// Post: a Queen is destructed
Queen::~Queen()
{
}
// Intent: get the value of Queen
// Pre: no variable required
// Post: return the value of Queen
int Queen::value() const
{
    return 9;
}
// Intent: check if Queen can move to the location
// Pre: location is a valid Square
// Post: return true if Queen can move to the location, false otherwise
bool Queen::canMoveTo(Square& location) const
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
    
    // valid move if moving on a clear diagonal
    else if(Board::getBoard()->isClearDiagonal(*(this->location()), location))
    {
        validMove = true;
    }
    
    
    return validMove;
}
// Intent: display the Queen
// Pre: no variable required
// Post: display the Queen
void Queen::display() const
{
    cout << _color + "Q";
}
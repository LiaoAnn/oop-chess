/***********************************************************************
 * File: bishop.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Definition of Bishop class
***********************************************************************/
#include "bishop.h"

// Intent: consturctor of Bishop
// Pre: isWhite is a bool that indicates the color of the piece
// Post: a Bishop object is created
Bishop::Bishop(bool isWhite) : Piece(isWhite)
{
}
// Intent: destructor of Bishop
// Pre: no variable required
// Post: a Bishop object is deleted
Bishop::~Bishop()
{
}
// Intent: return the value of Bishop
// Pre: no variable required
// Post: return the value of Bishop
int Bishop::value() const
{
    return 3;
}
// Intent: check if the Bishop can move to the location
// Pre: location is a Square object that indicates the location
// Post: return true if the Bishop can move to the location, false otherwise
bool Bishop::canMoveTo(Square& location) const
{
    bool validMove = false;
    
    // valid move if moving on a clear diagonal
    if(Board::getBoard()->isClearDiagonal(*(this->location()), location))
    {
        validMove = true;
    }
    
    return validMove;
}
// Intent: display the Bishop
// Pre: no variable required
// Post: display the Bishop
void Bishop::display() const
{
    cout << _color + "B";
}
/***********************************************************************
 * File: Pawn.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Pawn class
***********************************************************************/
#include "Pawn.h"
#include "Queen.h"
#include "Board.h"
// Intent: constructor of Pawn
// Pre: isWhite is a valid bool
// Post: a Pawn is constructed
Pawn::Pawn(bool isWhite) : RestrictedPiece(isWhite), _delegate(NULL)
{
}
// Intent: destructor of Pawn
// Pre: no variable required
// Post: a Pawn is destructed
Pawn::~Pawn()
{
	if (_delegate)
		delete _delegate;
}
// Intent: set the location of Pawn
// Pre: location is a valid Square
// Post: the location of Pawn is set
void Pawn::setLocation(Square* location)
{
	Piece::setLocation(location);
}
// Intent: get the value of Pawn
// Pre: no variable required
// Post: return the value of Pawn
int Pawn::value() const
{
	return _value;
}
// Intent: move Pawn to the location
// Pre: byPlayer is a valid Player, to is a valid Square
// Post: return true if Pawn is moved to the location, false otherwise
bool Pawn::moveTo(Player& byPlayer, Square& to)
{
	bool valid = false;

	// if the pawn has been promoted
	if (_delegate)
	{
		// use delegate piece's movement rules to determine validity
		valid = _delegate->moveTo(byPlayer, to);

		// if the move is valid, move the pawn:
		if (valid)
		{
			// unset the pawn's current square's occupant
			location()->setOccupier(NULL);

			// set this pawn's new location
			setLocation(&to);

			// set new square's occupant
			location()->setOccupier(this);
		}
	}
	else
	{
		// otherwise, attempt to move normally as a pawn
		valid = RestrictedPiece::moveTo(byPlayer, to);

		// if the move is valid and the pawn has reached the 
		// opponent's edge of the board, promote the pawn to
		// a queen
		if (valid)
		{
			if (Board::getBoard()->isEndRow(*location()))
			{
				_delegate = new Queen(isWhite());
				_delegate->setLocation(location());
				_value = _delegate->value();
			}
		}
	}

	return valid;
}
// Intent: check if Pawn can move to the location
// Pre: location is a valid Square
// Post: return true if Pawn can move to the location, false otherwise
bool Pawn::canMoveTo(Square& location) const
{
	bool validMove = false;
	int translationX = location.getX() - this->location()->getX();
	int translationY = location.getY() - this->location()->getY();
	int forward = 1;
	int locaY = 2;
	if (isWhite())
	{
		forward = -1;
		locaY = 5;
	}
		
	// if pawn has been promoted, use it's delegate's movement rules:
	if (_delegate)
	{
		validMove = _delegate->canMoveTo(location);
	}
	// otherwise, use normal pawn movement rules:
	else
	{
		// ("forward" is "backwards" relative to the board for black pieces)
		if (!isWhite())
		{
			translationX *= -1;
			translationY *= -1;
		}

		// valid move if moving 1 square forward to unoccupied square
		if (!location.occupied() && translationY == 1 && translationX == 0)
		{
			validMove = true;
		}
		// valid move if !moved and moving 2 squares forward
		// to unoccupied square along a clear vertical
		else if (!location.occupied() && !hasMoved() && translationY == 2 && translationX == 0 && Board::getBoard()->isClearVertical(*(this->location()), location))
		{
			validMove = true;
		}

		// valid move if capturing a piece on adjacent diagonal
		else if (location.occupied() && translationY == 1 && (translationX == 1 || translationX == -1))
		{
			validMove = true;
		}
		else if (translationY == 1 && translationX == 1 && Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupied())
		{

			if (Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->value() == 1 && location.getY() == locaY)
			{
				if (Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->hasMoved() == 1&& Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->isLastMove())

					validMove = true;
			}
		}
		else if (translationY == 1 && translationX == -1 && Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupied())
		{
			if (Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->value() == 1&& location.getY()==locaY)
			{
				if (Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->hasMoved() == 1 && Board::getBoard()->squareAt(location.getX(), location.getY() + forward)->occupiedBy()->isLastMove())
					validMove = true;
			}

		}
	}

	return validMove;
}
// Intent: display Pawn
// Pre: no variable required
// Post: Pawn is displayed
void Pawn::display() const
{
	if (_delegate)
	{
		_delegate->display();
	}
	else
	{
		cout << _color + "P";
	}
}


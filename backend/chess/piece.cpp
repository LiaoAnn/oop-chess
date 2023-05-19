/***********************************************************************
 * File: Piece.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Piece class
***********************************************************************/
#include <string>
#include "Piece.h"
#include "Player.h"
// Intent: constructor of Piece
// Pre: isWhite is a valid bool
// Post: a Piece is constructed
Piece::Piece(bool isWhite) : _isWhite(isWhite), _square(NULL)
{
	if (isWhite)
		_color = "W";
	else
		_color = "B";
}
// Intent: destructor of Piece
// Pre: no variable required
// Post: a Piece is destructed
Piece::~Piece()
{
}
// Intent: move the piece to the location
// Pre: byPlayer is a valid Player, toSquare is a valid Square
// Post: return true if the piece is moved to the location, false otherwise
bool Piece::moveTo(Player& byPlayer, Square& toSquare)
{
	bool validMove = false;
	bool isPass = false;
	Piece* toCapture = NULL;
	Square* fromSquare = _square;
	int forward = 1;
	int locaY = 2;
	if (_isWhite)
	{
		forward = -1;
		locaY = 5;
	}
	// check if this is being moved by its player
	if (_isWhite == byPlayer.isWhite())
	{
		// check if this is moving according to the correct geometry
		if (canMoveTo(toSquare))
		{
			// check if toSquare is occupied by a piece that could be captured
			if (toSquare.occupied())
			{
				toCapture = toSquare.occupiedBy();

				// move only valid if piece to capture is of different color
				if (toCapture->isWhite() != byPlayer.isWhite())
				{
					validMove = true;
				}
			}
			// Pawn special case: passers by
			else if (fromSquare->occupiedBy()->value() == 1 && fromSquare->getX() != toSquare.getX() && !toSquare.occupied())
			{
				toCapture = Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward)->occupiedBy();
				isPass = true;
				validMove = true;
			}
			// if there isn't a capture and we've made it this far, the move is valid
			else
			{
				validMove = true;
			}

			if (validMove)
			{
				// tentatively make the move:
				// tentatively take opponent's piece off the board, if needed
				if (toCapture)
				{
					toCapture->setLocation(NULL);
					if (isPass)
						Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward)->setOccupier(NULL);
				}
				// unset this piece's current square's occupant
				_square->setOccupier(NULL);

				// set this piece's new location
				_square = &toSquare;

				// set new square's occupant
				_square->setOccupier(this);

				// check if the move leaves byPlayer's king in check
				if (byPlayer.inCheck())
				{
					// if in check, move is invalid
					validMove = false;

					// undo the move:
					// reset this piece's location
					_square = fromSquare;

					// update the square's occupant
					_square->setOccupier(this);

					// reset the other square's occupant with opponent's piece or NULL
					if (!isPass)
						toSquare.setOccupier(toCapture);
					else
					{
						toSquare.setOccupier(NULL);
						toCapture->setLocation(Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward));
						Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward)->setOccupier(toCapture);
					}
					// if a piece was tentatively captured, put it back
					if (toCapture)
					{
						toCapture->setLocation(&toSquare);
					}
				}
				else
				{
					// if not in check, move is valid, so actually
					// capture the opponent's piece, if needed
					if (toCapture)
					{
						byPlayer.capture(toCapture);
					}
				}
			}
		}
	}

	return validMove;
}
// Intent: check if the piece can move to the location
// Pre: toSquare is a valid Square
// Post: return true if the piece can move to the location, false otherwise
bool Piece::hasMove(Player& byPlayer, Square& toSquare)
{
	bool validMove = false;
	bool isPass = false;
	Piece* toCapture = NULL;
	Square* fromSquare = _square;
	int forward = 1;
	int locaY = 2;
	if (_isWhite)
	{
		forward = -1;
		locaY = 5;
	}
	// check if this is being moved by its player
	if (_isWhite == byPlayer.isWhite())
	{
		// check if this is moving according to the correct geometry
		if (canMoveTo(toSquare))
		{
			// check if toSquare is occupied by a piece that could be captured
			if (toSquare.occupied())
			{
				toCapture = toSquare.occupiedBy();

				// move only valid if piece to capture is of different color
				if (toCapture->isWhite() != byPlayer.isWhite())
				{
					validMove = true;
				}
			}
			// Pawn special case: passers by
			else if (fromSquare->occupiedBy()->value() == 1 && fromSquare->getX() != toSquare.getX() && !toSquare.occupied())
			{
				toCapture = Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward)->occupiedBy();
				isPass = true;
				validMove = true;
			}
			// if there isn't a capture and we've made it this far, the move is valid
			else
			{
				validMove = true;
			}

			if (validMove)
			{
				// tentatively make the move:
				// tentatively take opponent's piece off the board, if needed
				if (toCapture)
				{
					toCapture->setLocation(NULL);
				}

				// unset this piece's current square's occupant
				_square->setOccupier(NULL);

				// set this piece's new location
				_square = &toSquare;

				// set new square's occupant
				_square->setOccupier(this);

				// check if the move leaves byPlayer's king in check
				if (byPlayer.inCheck())
				{
					// if in check, move is invalid
					validMove = false;
				}
				// undo the move:
				// reset this piece's location
				_square = fromSquare;

				// update the square's occupant
				_square->setOccupier(this);

				// reset the other square's occupant with opponent's piece or NULL
				if (!isPass)
					toSquare.setOccupier(toCapture);
				else
				{
					toSquare.setOccupier(NULL);
					toCapture->setLocation(Board::getBoard()->squareAt(toSquare.getX(), toSquare.getY() + forward));
				}
				// if a piece was tentatively captured, put it back
				if (toCapture)
				{
					toCapture->setLocation(&toSquare);
				}
			}
		}
	}
	return validMove;
}
// Intent: set the location of the piece
// Pre: location is a valid Square
// Post: the location of the piece is set
void Piece::setLocation(Square* location)
{
	_square = location;
}
// Intent: check if the piece is white
// Pre: no variable required
// Post: return true if the piece is white, false otherwise
bool Piece::isWhite() const
{
	return _isWhite;
}
// Intent: get the color of the piece
// Pre: no variable required
// Post: return the color of the piece
string Piece::color() const
{
	return _color;
}
// Intent: check if the piece is on the square
// Pre: no variable required
// Post: return true if the piece is on the square, false otherwise
bool Piece::isOnSquare() const
{
	return _square;
}
// Intent: get the location of the piece
// Pre: no variable required
// Post: return the location of the piece
Square* Piece::location() const
{
	return _square;
}

int Piece::hasMoved()
{
	return _moved;
}

void Piece::setLastMove(bool moved)
{
	lastMove = moved;
}

bool Piece::isLastMove()
{
	return lastMove;
}


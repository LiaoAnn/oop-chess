/***********************************************************************
 * File: Board.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Board class
***********************************************************************/
#include "Board.h"
#include "piece.h"

// Intent: constructor of Board
// Pre: no varable required
// Post: a Board object is created
Board::Board()
{
	// Set up squares (_DIMENSION x _DIMENSION)
	for (int i = 0; i < _DIMENSION; i++)
	{
		for (int j = 0; j < _DIMENSION; j++)
		{
			_squares[i][j] = new Square(i, j);
		}
	}
}
// Intent: destructor of Board
// Pre: no variable required
// Post: a Board object is deleted
Board::~Board()
{
	// Delete squares
	for (int i = 0; i < _DIMENSION; i++)
	{
		for (int j = 0; j < _DIMENSION; j++)
		{
			delete[] _squares[i][j];
		}
		delete[] _squares[i];
	}
	delete[] _squares;
}
// Intent: return the Board
// Pre: no variable required
// Post: return the Board
Board* Board::getBoard()
{
	if (!_theBoard)
		_theBoard = new Board();
	return _theBoard;
}
// Intent: return the square at the location
// Pre: x and y are int that indicates the location
// Post: return the square at the location
Square* Board::squareAt(int x, int y) const
{
	return _squares[x][y];
}
// Intent: check if the vertical is clear
// Pre: from and to are Square objects that indicates the location
// Post: return true if the vertical is clear, false otherwise
bool Board::isClearVertical(Square& from, Square& to) const
{
	Square* start = NULL;
	Square* end = NULL;
	bool valid = true;

	// determine which square has the smaller y-value, 
	// (this helps to determine which direction to travel in)
	if (from.getY() <= to.getY())
	{
		start = &from;
		end = &to;
	}
	else
	{
		start = &to;
		end = &from;
	}

	// check that there is no horizontal movement
	if (start->getX() != end->getX())
	{
		valid = false;
	}
	else
	{
		// iterate over vertical interval between squares
		for (int i = start->getY() + 1; i < end->getY(); i++)
		{
			// if a square is occupied, the vertical is not clear
			if (squareAt(start->getX(), i)->occupied())
			{
				valid = false;
			}
		}
	}

	return valid;
}
// Intent: check if the horizontal is clear
// Pre: from and to are Square objects that indicates the location
// Post: return true if the horizontal is clear, false otherwise
bool Board::isClearHorizontal(Square& from, Square& to) const
{
	Square* start = NULL;
	Square* end = NULL;
	bool valid = true;

	// determine which square has the smaller x-value, 
	// (this helps to determine which direction to travel in)
	if (from.getX() <= to.getX())
	{
		start = &from;
		end = &to;
	}
	else
	{
		start = &to;
		end = &from;
	}

	// check that there is no vertical movement
	if (start->getY() != end->getY())
	{
		valid = false;
	}
	else
	{
		// iterate over horizontal interval between squares
		for (int i = start->getX() + 1; i < end->getX(); i++)
		{
			// if a square is occupied, the vertical is not clear
			if (squareAt(i, start->getY())->occupied())
			{
				valid = false;
			}
		}
	}

	return valid;
}
// Intent: check if the diagonal is clear
// Pre: from and to are Square objects that indicates the location
// Post: return true if the diagonal is clear, false otherwise
bool Board::isClearDiagonal(Square& from, Square& to) const
{
	bool valid = true;
	int translationX = to.getX() - from.getX();
	int translationY = to.getY() - from.getY();
	int xDir = 1;
	int yDir = 1;

	if (translationX < 0)
	{
		xDir = -1;
	}

	if (translationY < 0)
	{
		yDir = -1;
	}

	// not a diagonal if absolute value of x and y translations don't match
	if (abs(translationX) != abs(translationY))
	{
		valid = false;
	}
	else
	{
		// iterate over diagonal interval between squares
		for (int i = 1; i < abs(translationX); i++)
		{
			// if a square is occupied, the diagonal is not clear
			if (squareAt(from.getX() + (i * xDir), from.getY() + (i * yDir))->occupied())
			{
				valid = false;
			}
		}
	}

	return valid;
}
// Intent: check if the path is clear
// Pre: from and to are Square objects that indicates the location
// Post: return true if the path is clear, false otherwise
bool Board::isEndRow(Square& location) const
{
	return (location.getY() == 0 || location.getY() == (_DIMENSION - 1));
}
// Intent: display the board
// Pre: outStream is an ostream object
// Post: the board is displayed
void Board::display(ostream& outStream) const
{
	// display each square and any pieces on the board
	outStream << endl << "   a  b  c  d  e  f  g  h" << endl;
	outStream << " -------------------------" << endl;
	for (int y = _DIMENSION - 1; y >= 0; y--) // display black at top, white at bottom
	{
		outStream << y + 1;
		for (int x = 0; x < _DIMENSION; x++)
		{
			outStream << "|";
			if (_squares[x][y]->occupied())
				_squares[x][y]->occupiedBy()->display();
			else
				outStream << "  ";
		}
		outStream << "|" << y + 1 << endl << " -------------------------" << endl;
	}
	outStream << "   a  b  c  d  e  f  g  h" << endl << endl;
}

Board* Board::_theBoard = NULL;
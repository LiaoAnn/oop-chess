/***********************************************************************
 * File: Board.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Board class
***********************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include "Square.h"

using namespace std;

class Board
{
public:
	~Board();
	static Board* getBoard();
	Square* squareAt(int x, int y) const;
	bool isClearVertical(Square& from, Square& to) const;
	bool isClearHorizontal(Square& from, Square& to) const;
	bool isClearDiagonal(Square& from, Square& to) const;
	bool isEndRow(Square& location) const;
	void display(ostream& outStream) const;
private:
	Board();
	static Board* _theBoard;
	static const int _DIMENSION = 8;
	Square* _squares[_DIMENSION][_DIMENSION];

};

#endif

/***********************************************************************
 * File: Rook.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Rook class
***********************************************************************/

#ifndef ROOK_H
#define ROOK_H

#include <iostream>
#include "RestrictedPiece.h"
#include "square.h"

using namespace std;

class Rook : public RestrictedPiece
{
public:

	/**
	* Creates a Rook
	*
	* @param color the color of the piece
	*/
	Rook(bool isWhite);

	/**
	 * Default destructor
	 */
	~Rook();

	/**
	* Get the point value of the piece
	*
	* @return the value
	*/
	int value() const;

	/**
	* Determines if the piece can legally move to a given square
	*
	* @param square the square to move to
	* @return if move is legal
	*/
	bool canMoveTo(Square& location) const;

	/**
	 * Display the piece
	 * @param outStream the output stream
	 */
	void display() const;

}; // Rook

#endif

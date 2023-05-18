/***********************************************************************
 * File: RestrictedPiece.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: RestrictedPiece class
***********************************************************************/

#ifndef RESTRICTED_H
#define RESTRICTED_H

#include "Piece.h"

class Player;

using namespace std;

class RestrictedPiece : public Piece
{
public:
	RestrictedPiece(bool isWhite);
	virtual ~RestrictedPiece();
	virtual bool moveTo(Player& byPlayer, Square& to);
	int hasMoved() const;

private:

};

#endif
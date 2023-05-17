/***********************************************************************
 * File: player.cpp
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implementation of Player class
***********************************************************************/
#include <iostream>
#include "player.h"
#include "board.h"
#include "game.h"

#define X_MIN 'a'
#define X_MAX 'h'
#define Y_MIN '1'
#define Y_MAX '8'

// Intent: constructor of Player
// Pre: name is a valid string, isWhite is a valid bool, myKing is a valid King, myPieces is a valid set of Piece
// Post: a Player is constructed
Player::Player(string name, bool isWhite, King& myKing, set<Piece*>& myPieces) :name(name), white(isWhite), myPieces(myPieces), myKing(myKing)
{
}
// Intent: destructor of Player
// Pre: no variable required
// Post: a Player is destructed
Player::~Player()
{
}
// Intent: player move a piece
// Pre: fromSquare and toSquare are valid string
// Post: return true if the piece is moved to the location, false otherwise
bool Player::makeMove(string fromSquare, string toSquare)
{
	int fromX;
	int fromY;
	int toX;
	int toY;

	// check/announce if player is in check
	if (inCheck())
	{
		cout << name << " is in check!" << endl;
	}
	if (!(Board::getBoard()->squareAt(tolower(fromSquare.at(0)) - X_MIN, tolower(fromSquare.at(1)) - Y_MIN)->occupied())) // the square isn't occupied
	{
		return false;
	}

	// translate input (algebraic notation) into board coordinates
	fromX = tolower(fromSquare.at(0)) - X_MIN;
	fromY = tolower(fromSquare.at(1)) - Y_MIN;
	toX = tolower(toSquare.at(0)) - X_MIN;
	toY = tolower(toSquare.at(1)) - Y_MIN;
	// move the piece on fromSquare to toSquare
	return Board::getBoard()->squareAt(fromX, fromY)->occupiedBy()->moveTo(*this, *(Board::getBoard()->squareAt(toX, toY)));
}
// Intent: check if the player is in check
// Pre:  no variable required
// Post: return true if the player is in check, false otherwise
bool Player::inCheck()
{
	bool check = false;

	// for each piece in the opponent's set of pieces
	for (set<Piece*>::iterator itr = Game::opponentOf(*this)->getMyPieces()->begin(); itr != Game::opponentOf(*this)->getMyPieces()->end(); ++itr)
	{
		// if a piece that is still located on the board
		// can move to my king's square
		if (((Piece*)*itr)->location() &&
			((Piece*)*itr)->canMoveTo(*(getMyKing()->location())))
		{
			// I am in check
			check = true;
		}
	}

	return check;
}
// Intent: move a piece
// Pre: aPiece is a valid Piece
// Post: aPiece is added to the set of captured pieces
void Player::capture(Piece* aPiece)
{
	// unset the piece's location on the board
	aPiece->setLocation(NULL);

	// put the piece into this player's set of captured pieces
	capturedPieces.insert(aPiece);
}
// Intent: get the name of the player
// Pre: no variable required
// Post: return the name of the player
string Player::getName() const
{
	return name;
}
// Intent: get the color of the player
// Pre: no variable required
// Post: return true if the player is white, false otherwise
bool Player::isWhite() const
{
	return white;
}
// Intent: get the score of the player
// Pre: no variable required
// Post: return the score of the player
int Player::score() const
{
	int score = 0;

	// add up the points of all captured pieces
	for (set<Piece*>::iterator itr = capturedPieces.begin(); itr != capturedPieces.end(); ++itr)
	{
		score += ((Piece*)*itr)->value();
	}

	return score;
}
// Intent: get the set of captured pieces
// Pre: no variable required
// Post: return the set of captured pieces
set<Piece*>* Player::getMyPieces() const
{
	return &myPieces;
}
// Intent: get the king of the player
// Pre: no variable required
// Post: return the king of the player
King* Player::getMyKing() const
{
	return &myKing;
}
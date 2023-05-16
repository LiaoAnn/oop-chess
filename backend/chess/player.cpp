/*
 *  player.cpp
 *  ChessProject
 *
 */
#include <iostream>
#include "player.h"
#include "board.h"
#include "game.h"

#define X_MIN 'a'
#define X_MAX 'h'
#define Y_MIN '1'
#define Y_MAX '8'

Player::Player(string name, bool isWhite, King& myKing, set<Piece*>& myPieces) :name(name), white(isWhite), myPieces(myPieces), myKing(myKing)
{
}

Player::~Player()
{
}

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

void Player::capture(Piece* aPiece)
{
	// unset the piece's location on the board
	aPiece->setLocation(NULL);

	// put the piece into this player's set of captured pieces
	capturedPieces.insert(aPiece);
}

string Player::getName() const
{
	return name;
}

bool Player::isWhite() const
{
	return white;
}

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

set<Piece*>* Player::getMyPieces() const
{
	return &myPieces;
}

King* Player::getMyKing() const
{
	return &myKing;
}
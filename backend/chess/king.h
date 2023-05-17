/***********************************************************************
 * File: king.h
 * Author: 劉沛安
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: king class
***********************************************************************/

#ifndef KING_H
#define KING_H

#include <iostream>
#include "restrictedPiece.h"

using namespace std;

class King : public RestrictedPiece
{
 public:
    King(bool isWhite);
    ~King();
    int value() const;
    bool canMoveTo(Square& location) const;
    void display() const;

};

#endif

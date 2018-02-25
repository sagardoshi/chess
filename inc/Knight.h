#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
private:
public:
    Knight(int, int, bool); /* Constructor calls base class constructor */
    ~Knight();

    /* Need special handling for knight bc it leaps over middle enemies */
    bool pathIsClear(int, int, ChessPiece*, ChessPiece *[FILES][RANKS]);
    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);
};

#endif

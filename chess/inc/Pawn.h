#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(int, int, bool); /* Constructor calls base class constructor */
    ~Pawn();

    /* Need special handling for pawn bc diag move not OK if no enemy */
    bool pathIsClear(int, int, ChessPiece*, ChessPiece *[FILES][RANKS]);
    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);

};

#endif

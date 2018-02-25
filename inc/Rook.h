#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece {
private:
public:
    Rook(int, int, bool); /* Constructor calls base class constructor */
    ~Rook();

    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);
};

#endif

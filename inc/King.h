#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
private:
public:
    King(int, int, bool); /* Constructor calls base class constructor */
    ~King();

    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);
};

#endif

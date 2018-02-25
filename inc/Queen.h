#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece {
private:
public:
    Queen(int, int, bool); /* Constructor calls base class constructor */
    ~Queen();

    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);
};

#endif

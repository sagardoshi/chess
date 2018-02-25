#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
private:
public:
    Bishop(int, int, bool);  /* Constructor calls base class constructor */
    ~Bishop();

    /* Each piece makes sure the actual movement works */
    bool displacementOK(int, int);
};

#endif

#include "../inc/Knight.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Knight::Knight(int f, int r, bool c) : ChessPiece(f, r, c, "Knight") {}

Knight::~Knight() {}

bool Knight::pathIsClear(int hMove, int vMove, ChessPiece* target,
                         ChessPiece* board[FILES][RANKS]) {

    // Path not clear if a friendly piece is at destination
    if (target != NULL && (target->isPieceWhite() == isWhite)) return false;

    return true; // Jumping knight doesn't care what else is along the way
}

bool Knight::displacementOK(int hMove, int vMove) {
    if (hMove == 0 && vMove == 0) return false;           // can't stay still
    if (abs(hMove) != 1 && abs(hMove) != 2) return false; // hMove must be 1 / 2
    if (abs(vMove) != 1 && abs(vMove) != 2) return false; // vMove must be 1 / 2
    if (abs(hMove) == abs(vMove)) return false;           // L-shape only

    return true;
}

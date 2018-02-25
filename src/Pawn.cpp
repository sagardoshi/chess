#include "../inc/Pawn.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Pawn::Pawn(int f, int r, bool c) :
           ChessPiece(f, r, c, "Pawn") {
}

Pawn::~Pawn() {
};

bool Pawn::pathIsClear(int hMove, int vMove, ChessPiece* target,
                       ChessPiece* board[FILES][RANKS]) {
    // Path not clear if a friendly piece is at destination
    if (target != NULL && (target->isPieceWhite() == isWhite)) return false;

    // Check only necessary if first move has a double step
    if (!noPieceInMiddle(hMove, vMove, board)) return false;

    // Special for pawn: diagonal not allowable if destination is empty
    if (abs(hMove) == 1 && abs(vMove) == 1 && target == NULL) return false;
    return true;
}

bool Pawn::displacementOK(int hMove, int vMove) {

    if (vMove == 0) return false; // Must go vert... No pure horizontal movement
    if (isWhite && (vMove < 0)) return false; // White pawns must go up
    if (!isWhite && (vMove > 0)) return false; // Black pawns must go down
    if (abs(hMove) > 1) return false; // Never move >1 step horizontally

    if (isFirstMove) {
        if (abs(vMove) != 1 && abs(vMove) != 2) return false; // 1 or 2 at first
        if (abs(vMove) == 2 && hMove != 0) return false; // No horiz if moving 2
    } else {
        if (abs(vMove) != 1) return false; // 1 max after first move
    }

    return true;
}

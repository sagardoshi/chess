#include "../inc/King.h"

#include <cstdlib>
#include <iostream>

using namespace std;

King::King(int f, int r, bool c) : ChessPiece(f, r, c, "King") {}

King::~King() {}

bool King::displacementOK(int hMove, int vMove) {
    if (hMove == 0 && vMove == 0) return false; // can't stay still

    if (abs(hMove) > 1) return false; // King can only go <= 1 step horizontally
    if (abs(vMove) > 1) return false; // King can only go <= 1 step vertically

    return true;
}

#include "../inc/Queen.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Queen::Queen(int f, int r, bool c) : ChessPiece(f, r, c, "Queen") {}

Queen::~Queen() {}

bool Queen::displacementOK(int hMove, int vMove) {
    if (hMove == 0 && vMove == 0) return false; // Cannot stay still

    // If there is movement in H and V, and the distances are not equal, false
    if (hMove != 0 && vMove != 0 && (abs(vMove) != abs(hMove))) return false;

    return true;
}

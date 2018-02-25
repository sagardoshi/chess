#include "../inc/Bishop.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Bishop::Bishop(int f, int r, bool c) : ChessPiece(f, r, c, "Bishop") {}

Bishop::~Bishop() {}

bool Bishop::displacementOK(int hMove, int vMove) {
    if (hMove == 0 || vMove == 0) return false; // Can't stay put in either dir
    if (abs(hMove) != abs(vMove)) return false; // Must move same amount h and v

    return true;
}

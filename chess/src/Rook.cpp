#include "../inc/Rook.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Rook::Rook(int f, int r, bool c) : ChessPiece(f, r, c, "Rook") {}

Rook::~Rook() {}

bool Rook::displacementOK(int hMove, int vMove) {
    if (hMove == 0 && vMove == 0) return false; // Cannot stay still
    if (hMove != 0 && vMove != 0) return false; // Rooks only move in one way

    return true;
}

#ifndef PIECE_ALLOCATION_H
#define PIECE_ALLOCATION_H

#include "globals.h"
#include "ChessPiece.h"

#include <iostream>
using namespace std;

template <typename T>
class PieceAllocation {
public:
    PieceAllocation(ChessPiece* square[FILES][RANKS], int leftFile,
                    int whiteRank, int gap) {
        int file = leftFile - 1; // Subtracting 1 for 0-indexing
        int wRank = whiteRank - 1; // Subtracting 1 for 0-indexing
        int bRank = RANKS - whiteRank; // (8 - white's rank)... flips the board

        for (int f = file; f < FILES; f = f + gap) {
            square[f][wRank] = new T(f, wRank, true);  // true means white piece
            square[f][bRank] = new T(f, bRank, false); // opposite for black
        }
    }
};

#endif

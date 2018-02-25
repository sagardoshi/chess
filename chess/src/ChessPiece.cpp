#include "../inc/ChessPiece.h"

#include <iostream>
#include <cstring>
#include <assert.h>


using namespace std;

ChessPiece::ChessPiece(int f, int r, bool colour, const char* n) :
    file(f), rank(r), isWhite (colour), isFirstMove(1),
    captures(0), moveCount(0), name(n) {
}

ChessPiece::~ChessPiece() {}

/********************************************************/
/******* Quick getters, incrementers, and toggles *******/
/********************************************************/

bool ChessPiece::isPieceWhite()        { return isWhite;      }
const char* ChessPiece::getPieceType() { return name;         }
void ChessPiece::markCapture()         { captures++;          }
int ChessPiece::getCaptures()          { return captures;     }
void ChessPiece::markMoveCount()       { moveCount++;         }
int ChessPiece::getMoves()             { return moveCount;    }
void ChessPiece::noLongerFirstMove()   { isFirstMove = false; }

const char* ChessPiece::getColourName() {
    if (isWhite) return "White";
    else return "Black";
}

void ChessPiece::setNewPos(int newFile, int newRank) {
    file = newFile;
    rank = newRank;
}


/**************************************************/
/******* Methods to verify validity of move *******/
/**************************************************/


bool ChessPiece::isValidMove(int destFR[2], ChessPiece* board[FILES][RANKS]) {
    int destFile = destFR[0];
    int destRank = destFR[1];

    int hMove = destFile - file;
    int vMove = destRank - rank;
    ChessPiece* target = board[destFile][destRank];

    // Invalid if going off board
    if (!stayingOnBoard(destFile, destRank))       return false;
    if (!pathIsClear(hMove, vMove, target, board)) return false;
    if (!displacementOK(hMove, vMove))             return false;

    // If a pawn not moving horizontally, with an enemy at destination...
    if (!strcmp(name, "Pawn") && hMove == 0 &&
        target != NULL && (target->isPieceWhite() != isWhite)) {
        return false; // Cannot move
    }

    return true;
}

bool ChessPiece::stayingOnBoard(int destFile, int destRank) {
    if (destFile < 0 || destFile >= FILES) return false;
    if (destRank < 0 || destRank >= RANKS) return false;
    return true;
}

bool ChessPiece::pathIsClear(int hMove, int vMove, ChessPiece* target,
                             ChessPiece* board[FILES][RANKS]) {
    // Invalid if friendly piece at destination
    if (target != NULL && (target->isPieceWhite() == isWhite)) return false;

    // Path blocked if ANY piece is along the way
    if (!noPieceInMiddle(hMove, vMove, board)) return false;
    return true;
}

bool ChessPiece::noPieceInMiddle(int hMove, int vMove,
                                 ChessPiece* board[FILES][RANKS]) {
   // If ANY piece, no matter the colour, is in the middle, rook is blocked
   ChessPiece* nextSquare = NULL;

   // If H_STEP and V_STEP are both nonzero, then diagonal movement
   const int H_STEP = setStep(hMove); // -1 or +1
   const int V_STEP = setStep(vMove); // -1 or +1
   int hDisplacement = H_STEP; // will be our incrementing num (unless 0)
   int vDisplacement = V_STEP; // will be our incrementing num (unless 0)


   // Check squares in direction of move, excluding origin and destination
   while (hMove != hDisplacement || vMove != vDisplacement) {
       nextSquare = board[file + hDisplacement][rank + vDisplacement];
       if (nextSquare != NULL) return false; // blocked no matter the colour

       // Move 1 square displacement in the direction of destination
       hDisplacement += H_STEP;
       vDisplacement += V_STEP;
   }
   return true;
}

int ChessPiece::setStep(int move) {
    if      (move > 0) return 1;
    else if (move < 0) return -1;
    else               return 0;
}

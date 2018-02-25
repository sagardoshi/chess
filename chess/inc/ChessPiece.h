#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "globals.h"

class ChessPiece {
protected:
    int file, rank;
    bool isWhite, isFirstMove;
    int captures, moveCount;
    const char* name; // Max size of piece name is 6 characters

public:
    ChessPiece(int, int, bool, const char*);
    virtual ~ChessPiece();

    /******* Quick getters, incrementers, and toggles *******/

    /* Get true if white, false if black */
    bool isPieceWhite();
    /* Get string name of piece */
    const char* getPieceType();
    /* Increment a piece's capture count for end game stats */
    void markCapture();
    /* Get total captures of this piece */
    int getCaptures();
    /* Increment number of times piece moved */
    void markMoveCount();
    /* Get total move count of this piece */
    int getMoves();
    /* Toggle off isFirstMove; most useful for pawns */
    void noLongerFirstMove();
    /* Returns colour as a cstring */
    const char* getColourName();
    /* Resets file and rank (in that order) */
    void setNewPos(int, int);


    /******* Methods to verify validity of move *******/

    /* Mother function for below three validity checks */
    bool isValidMove(int*, ChessPiece *[FILES][RANKS]);
    /* isValidMove Helper: Returns true if dest file or rank is off-board */
    bool stayingOnBoard(int, int);
    /* isValidMove Helper: ensures no other pieces on way to target */
    virtual bool pathIsClear(int, int, ChessPiece*, ChessPiece *[FILES][RANKS]);
    /* pathIsClear Helper: Given move direction, looks for intervening pieces */
    bool noPieceInMiddle(int, int, ChessPiece *[FILES][RANKS]);
    /* noPieceInMiddle Helper: returns -1, 1, or 0, if input's neg, pos, or 0 */
    int setStep(int);
    /* isValidMove Helper: but pure virtual as each piece type has own limits */
    virtual bool displacementOK(int, int) = 0;


};

#endif

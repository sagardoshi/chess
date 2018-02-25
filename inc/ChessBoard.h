#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"
#include "globals.h"

#include <sstream>


class ChessBoard {

private:
    ChessPiece* square[FILES][RANKS];
    int turn;



    /******* Internal utility methods *******/

    /* Mother function to the below two helpers */
    void setUpBoard();
    /* setUpBoard Helper: creates an null array of 8x8 ChessPieces */
    void createSquares();
    /* setUpBoard Helper: places 32 pieces on correct squares */
    void placePieces();
    /* resetBoard Helper: Sets squares to NULL, releases seized memory */
    void clearBoard();


    /******* submitMove's verification helpers *******/

    /* submitMove Helper: verifies inputs are clean */
    bool setValidInput(const char*, int*);
    /* setValidInput Helper: Abstract away variable initialisation */
    void setCoord(const char*, int*);
    /* submitMove Helper: Error if no piece at source location */
    bool noPieceAtLoc(ChessPiece*, const char*);
    /* submitMove Helper: Error if wrong player trying to move */
    bool turnOrderIsCorrect(bool);


    /******* Functions to mark the end of the game *******/

    /* Prints final messages, counts up stats, and ends game */
    void runGameOver(std::stringstream&, bool, bool);
    /* runGameOver Helper: Prints final board at end of game */
    void thankPlayersPrintSquares(std::stringstream& msg);
    /* runGameOver Helper: Child function to runGameOver */
    void addGameStats(std::stringstream&, bool);
    /* addGameStats Helper: locates pieces with cool stats */
    void findMaxPieces(bool, int&, int&, int&, int&, int&, int&);


    /******* Methods to help add messages to stream *******/

    /* Takes in a boolean for colour, and returns "White" or "Black" */
    const char* colourFromBool(bool);
    /* Adds player piece's colour and type into message stream */
    void addInitialMessage(std::stringstream&, ChessPiece*);
    /* Joins movement details to message stream */
    void addMoveMessage(std::stringstream&, const char*, const char*);
    /* Prints if checkmate occurred */
    void addCheckmateMessage(std::stringstream&, bool);
    /* Prints if stalemate occurred */
    void addStalemateMessage(std::stringstream&, bool);
    /* Prints if check occurred (would also print before either 'mate') */
    void addCheckMessage(std::stringstream&, bool);


    /******* Actual movement methods *******/

    /* Only is called if target square has opponent's piece */
    void recordAttack(ChessPiece*, ChessPiece*, std::stringstream&);
    /* Mother function to check for attack and manage movement */
    void makeMove(ChessPiece*, int*, int*, std::stringstream&);


    /******* Methods to check and verify move legality *******/

    /* Mother function for moveOK & printDenial */
    bool moveIsLegal(ChessPiece*, int*, int*, std::stringstream&, const char*);
    /* moveIsLegal Helper: if move not OK, outputs message to cerr */
    void printDenial(std::stringstream&, const char*);
    /* moveIsLegal Helper: Checks if piece can move without self-checking */
    bool moveOK(ChessPiece*, int*, int*);
    /* moveOK Helper: sees if future state results in check */
    bool safeFromSelfCheck(int*, int*);
    /* safeFromSelfCheck Helper: projects one step forward */
    void stepIntoFuture(ChessPiece*, int*, int*);
    /* safeFromSelfCheck Helper: undoes projection, regardless of self-check */
    void undoFuture(ChessPiece*, int*, int*);
    /* Checks if a given player is currently in check */
    bool isInCheck(bool);
    /* isInCheck Helper: sees if move will put own king in check */
    void getDefenderKingLoc(bool, int*);
    /* Checks every piece for one side to see if can safely go ANYwhere */
    bool playerHasLegalMove(bool);



public:
    /******* Utility methods to call from ChessMain.cpp *******/

    /* Constructor just calls setUpBoard()*/
    ChessBoard();
    /* Destructor  just calls clearBoard()*/
    ~ChessBoard();
    /* Mother function for clearBoard & setUpBoard again; also resets 'turn' */
    void resetBoard();
    /* Printing pointer for debugging */
    void printSquares();
    /* Most common method in ChessMain –- takes move inputs */
    void submitMove(const char*, const char*);

};

#endif

#include "../inc/globals.h"

#include "../inc/ChessPiece.h"
#include "../inc/ChessBoard.h"
#include "../inc/PieceAllocation.h"
#include "../inc/Pawn.h"
#include "../inc/Rook.h"
#include "../inc/Knight.h"
#include "../inc/Bishop.h"
#include "../inc/Queen.h"
#include "../inc/King.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <assert.h>

using namespace std;

/*******************************/
/******* Utility methods *******/
/*******************************/

ChessBoard::ChessBoard() : turn(0) {
    setUpBoard(); // Abstracting this for later reuse by resetBoard()
}

ChessBoard::~ChessBoard() {
    clearBoard(); // Abstracting this for later reuse by resetBoard()
}

void ChessBoard::setUpBoard() {
    createSquares(); // Abstracting board creation for readability
    placePieces();   // Assign the right number of pieces to the right squares
    cout << "A new chess game is started!" << endl;
}

void ChessBoard::createSquares() {
    for (int f = 0; f < FILES; f++) {
        for (int r = 0; r < RANKS; r++) {
            square[f][r] = NULL;
        }
    }
}

void ChessBoard::placePieces() {
    const int W_PAWN_RANK = 2; // 0-indexed rank of white pawns
    const int W_RANK = 1;

    enum LeftmostFile {
        pawnFile = 1,
        rookFile = 1,
        knightFile = 2,
        bishopFile = 3,
        queenFile = 4,
        kingFile = 5
    };

    enum HorizGaps {
        pawnGap = 1,
        rookGap = 7,
        knightGap = 5,
        bishopGap = 3,
        queenGap = FILES, // Only one queen, so break loop after just once thru
        kingGap = FILES   // Only one  king, so break loop after just once thru
    };

    PieceAllocation<Pawn> pawns(square, pawnFile, W_PAWN_RANK, pawnGap);
    PieceAllocation<Rook> rooks(square, rookFile, W_RANK, rookGap);
    PieceAllocation<Knight> knights(square, knightFile, W_RANK, knightGap);
    PieceAllocation<Bishop> bishops(square, bishopFile, W_RANK, bishopGap);
    PieceAllocation<Queen> queens(square, queenFile, W_RANK, queenGap);
    PieceAllocation<King> kings(square, kingFile, W_RANK, kingGap);

}


void ChessBoard::resetBoard() {
    turn = 0; // Reset global variable marking how long game takes
    clearBoard();
    setUpBoard();
}

void ChessBoard::clearBoard() {
    for (int f = 0; f < FILES; f++) {
        for (int r = (RANKS - 1); r >= 0; r--) {
            if (square[f][r] != NULL) { // If not null, there is a piece there
                delete square[f][r];    // Deallocate memory for that piece
                square[f][r] = NULL;    // And reset pointer to NULL
            }
        }
    }
}



void ChessBoard::printSquares() {
    ChessPiece* ptr = NULL;

    cout << " ________________________________________________________________";
    cout << "______" << endl;
    for (int r = RANKS - 1; r >= 0; r--) {
        cout << "|";
        for (int f = 0; f < FILES; f++) {
            ptr = square[f][r];
            if (ptr == NULL) {
                cout << "       | ";
            } else {
                const char* name = ptr->getPieceType();
                if (!strcmp(name, "Queen")) cout << name << " " << " | ";
                else if (!strcmp(name, "Knight") || !strcmp(name, "Bishop"))
                    cout << name << " | ";
                else cout << " " << name << " " << " | ";
            }
        }
        cout << endl;
        cout << "|";
        for (int f = 0; f < FILES; f++) {
            ptr = square[f][r];
            if (ptr == NULL) {
                cout << " (" << static_cast<char>(f + 'A') << (r + 1) <<")  | ";
            } else {
                if (ptr->isPieceWhite()) cout << "  -w- " << " | ";
                else cout << "  -b- " << " | ";
            }
        }
        cout << "\n|_______|________|________|________|________|________|_____";
        cout << "___|________|" << endl;
    }
    cout << endl;

}


void ChessBoard::submitMove(const char* from, const char* to) {
    stringstream message; // Will be periodically supplemented
    int fromFR[2], toFR[2];

    /************** Verify inputs **************/

    // If inputs are invalid, then return right away and output to cerr
    if (!setValidInput(from, fromFR)) return;
    if (!setValidInput(to, toFR)) return;
    assert(fromFR[0] >= 0 || fromFR[1] <= 7);
    assert(  toFR[0] >= 0 ||   toFR[1] <= 7);

    ChessPiece* piece = square[fromFR[0]][fromFR[1]]; // {fromF, fromR}

    if (noPieceAtLoc(piece, from)) return;
    assert(piece != NULL);             // By now, must be a piece at source loc
    addInitialMessage(message, piece); // so now we label that piece

    // Now that we know piece exists, record colours: 1 for white, 0 for black
    bool playerColour = piece->isPieceWhite();
    bool enemyColour = !playerColour;
    if (!turnOrderIsCorrect(playerColour)) return;

    /************** Check move legality **************/

    if (!moveIsLegal(piece, fromFR, toFR, message, to)) return;

    addMoveMessage(message, from, to); // Used in all later messages
    makeMove(piece, fromFR, toFR, message);

    /************** Check for endgame **************/

    bool enemyInCheck = isInCheck(enemyColour);
    bool enemyCanMove = playerHasLegalMove(enemyColour);

    if (!enemyCanMove) { // Then game must be over
        runGameOver(message, enemyInCheck, enemyColour);
        return;
    } else if (enemyInCheck) addCheckMessage(message, enemyColour);

    cout << message.str() << endl; // Prints move confirmation at end of turn

}

/*************************************************/
/******* submitMove's verification helpers *******/
/*************************************************/

bool ChessBoard::setValidInput(const char* input, int* coord) {
    int fileAsInt = input[0], rankAsInt = input[1];

    if (strlen(input) != 2 ||
        (fileAsInt < 'A' || fileAsInt > 'H') ||
        (rankAsInt < '1' || rankAsInt > '8')) {
        cerr << "Your inputted move, " << input << ", is invalid. Please use ";
        cerr << "the format \"B5\" in which the first character is an ";
        cerr << "uppercase letter from A through H and the second character ";
        cerr << "is an integer from 1 to 8.\n";
        return false;
    }

    // If the input is valid, fill coord with file and rank before returning
    setCoord(input, coord); // Set int[2] arrays as {file, rank}
    return true;
}


void ChessBoard::setCoord(const char* loc, int* coord) {
    int loadFile = loc[0] - 'A';     // Setting the char 'A' to the int 0;
    int loadRank = loc[1] - '0' - 1; // Setting the char '1' to the int 0
    coord[0] = loadFile;
    coord[1] = loadRank;
}

bool ChessBoard::noPieceAtLoc(ChessPiece* squareToCheck, const char* from) {
    if (squareToCheck == NULL) {
        cerr << "There is no piece at position " << from << "!\n";
        return true;
    }
    return false;
}

bool ChessBoard::turnOrderIsCorrect(bool isWhite) {
    const char*   colour = "White"; // default to white
    if (!isWhite) colour = "Black"; // change name if necessary

    // Make sure the correct colour is moving on its own turn (first white)
    if ((turn % 2 == 0 && !isWhite) || // If white's turn but black moves
        (turn % 2 == 1 && isWhite)) {  // If black's turn but white moves
        cerr << "It is not " << colour << "'s turn to move!" << endl;
        return false; // Submit move again without incrementing turn
    }
    return true;
}

/*****************************************************/
/******* Functions to mark the end of the game *******/
/*****************************************************/

void ChessBoard::runGameOver(stringstream& msg, bool enemyInCheck,
                             bool loserColour) {
    // Add end game messages
    if (enemyInCheck) addCheckmateMessage(msg, loserColour);
    else addStalemateMessage(msg, loserColour);

    addGameStats(msg, loserColour);

    thankPlayersPrintSquares(msg);
    clearBoard();
}

void ChessBoard::thankPlayersPrintSquares(stringstream& msg) {
    msg << "Below is the final state of the board. Thanks for playing!" << endl;
    cout << msg.str(); // Prints everything stored until now
    printSquares();
}

void ChessBoard::addGameStats(stringstream& msg, bool loserColour) {
    const char* winner = colourFromBool(!loserColour);
    int capF = -1, capR = -1, capMax = 0;
    int moveF = -1, moveR = -1, moveMax = 0;

    findMaxPieces(winner, capF, capR, capMax, moveF, moveR, moveMax);
    ChessPiece* capturesPiece = square[capF][capR];
    ChessPiece* movesPiece = square[moveF][moveR];

    // Print turn count
    msg << endl << "Congratulations, " << winner << " Player!" << endl;
    msg << "--You won after " << turn << " turns." << endl;

    // Print one live piece with most captures
    msg << "–-Your most deadly surviving piece: ";
    msg << capturesPiece->getPieceType() << " (";
    msg << static_cast<char>(capF + 'A') << capR + 1 << ") with ";
    msg << capMax << " capture(s)" << endl;

    // Print one live piece with most moves
    msg << "–-Your favourite surviving piece: ";
    msg << movesPiece->getPieceType() << " (" << static_cast<char>(moveF + 'A');
    msg << moveR + 1 << ") with " << moveMax << " move(s)" << endl;
}

void ChessBoard::findMaxPieces(bool winner, int& capF, int& capR, int& capMax,
                               int& moveF, int& moveR, int& moveMax) {
    // Check every square
    for (int f = 0; f < FILES; f++) {
        for (int r = 0; r < RANKS; r++) {
            // Consider any square with a piece on it...
            if (square[f][r] != NULL) {

                ChessPiece* piece = square[f][r];
                bool pieceColour = piece->isPieceWhite();

                // Consider only pieces of the player's colour...
                if (pieceColour == winner) {
                    int pieceCaptures = piece->getCaptures();
                    int pieceMoves = piece->getMoves();

                    // Save pieces with max captures
                    if (pieceCaptures > capMax) {
                        capMax = pieceCaptures;
                        capF = f;
                        capR = r;
                    }

                    // Save pieces with max moves (might also be maxCap piece)
                    if (pieceMoves > moveMax) {
                        moveMax = pieceMoves;
                        moveF = f;
                        moveR = r;
                    }

                }
            }
        }
    }
}

/******************************************************/
/******* Methods to help add messages to stream *******/
/******************************************************/

const char* ChessBoard::colourFromBool(bool white) {
    const char* output = "White";
    if (!white) output = "Black";
    return output;
}

void ChessBoard::addInitialMessage(stringstream& msg, ChessPiece* piece) {
    const char* fromColour = piece->getColourName(); //it must have colour
    const char* fromType = piece->getPieceType(); // and must have type.

    msg << fromColour << "'s " << fromType; // output always starts w/this
}

void ChessBoard::addMoveMessage(stringstream& msg,
                                const char* from, const char* to) {
    msg << " moves from " << from << " to " << to;
}

void ChessBoard::addCheckmateMessage(stringstream& msg, bool loserColour) {
    msg << endl << colourFromBool(loserColour) << " is in checkmate" << endl;
}

void ChessBoard::addStalemateMessage(stringstream& msg, bool loserColour) {
    msg << endl << colourFromBool(loserColour) << " is in stalemate" << endl;
}

void ChessBoard::addCheckMessage(stringstream& msg, bool defenderColour) {
    msg << endl << colourFromBool(defenderColour) << " is in check";
}

/***************************************/
/******* Actual movement methods *******/
/***************************************/

void ChessBoard::recordAttack(ChessPiece* attacker, ChessPiece* defender,
                              stringstream& msg) {

    const char* defenderColour = defender->getColourName();
    const char* defenderType =    defender->getPieceType();

    msg << " taking " << defenderColour << "'s " << defenderType;
    attacker->markCapture();
    delete defender;
}

void ChessBoard::makeMove(ChessPiece* movingPiece, int srcFR[2],
                          int destFR[2], stringstream& msg) {

    // If this triggers, target must be enemy; validity check covered friendlies
    const char* movingPieceName = movingPiece->getPieceType();
    ChessPiece* target = square[destFR[0]][destFR[1]];

    if (target != NULL) recordAttack(movingPiece, target, msg);
    stepIntoFuture(movingPiece, srcFR, destFR); // Same as in safeFromSelfCheck

    // Adjust major tracking vars, and hobble pawns after their first move
    turn++;
    movingPiece->markMoveCount();
    if (!strcmp(movingPieceName, "Pawn")) movingPiece->noLongerFirstMove();
}

/*********************************************************/
/******* Methods to check and verify move legality *******/
/*********************************************************/

bool ChessBoard::moveIsLegal(ChessPiece* piece, int fromFR[2], int toFR[2],
                             stringstream& msg, const char* to) {
    if (!moveOK(piece, fromFR, toFR)) {
        printDenial(msg, to);
        return false;
    }
    return true;
}

void ChessBoard::printDenial(stringstream& msg, const char* to) {
    msg << " cannot move to " << to << endl;
    cerr << msg.str();
}

bool ChessBoard::moveOK(ChessPiece* piece, int fromFR[2], int toFR[2]) {
    if (!safeFromSelfCheck(fromFR, toFR)) return false;
    if (!piece->isValidMove(toFR, square)) return false;
    return true;
}

bool ChessBoard::safeFromSelfCheck(int srcFR[2], int destFR[2]) {

    // Using extra variables for readability
    int dFile = destFR[0];
    int dRank = destFR[1];

    ChessPiece* movingPiece = square[srcFR[0]][srcFR[1]];
    ChessPiece* holder = NULL;

    bool colour = movingPiece->isPieceWhite();
    bool moveWouldNotSelfCheck = true; // true just as default value

    // To project without losing information, save "lost" piece temporarily
    if (square[dFile][dRank] != NULL) holder = square[dFile][dRank];

    stepIntoFuture(movingPiece, srcFR, destFR);
    if (isInCheck(colour)) moveWouldNotSelfCheck = false;
    undoFuture(movingPiece, srcFR, destFR); // Return to the present

    // To undo without losing information, restore "lost" piece before returning
    if (holder != NULL) square[dFile][dRank] = holder;

    return moveWouldNotSelfCheck;
}

void ChessBoard::stepIntoFuture(ChessPiece* movingPiece,
                                int srcFR[2], int destFR[2]) {
    // Using extra variables for readability
    int dFile = destFR[0];
    int dRank = destFR[1];
    int sFile = srcFR[0];
    int sRank = srcFR[1];

    square[dFile][dRank] = movingPiece; // dest square now points to movingPiece
    square[sFile][sRank] = NULL;        // source square now points to NULL
    movingPiece->setNewPos(dFile, dRank); // update internal data
}

void ChessBoard::undoFuture(ChessPiece* movingPiece,
                            int srcFR[2], int destFR[2]) {
    // Using extra variables for readability
    int dFile = destFR[0];
    int dRank = destFR[1];
    int sFile = srcFR[0];
    int sRank = srcFR[1];

    square[sFile][sRank] = square[dFile][dRank]; // Repoint src square to piece
    square[dFile][dRank] = NULL; // Point destination square to NULL (default)
    movingPiece->setNewPos(sFile, sRank);
}

bool ChessBoard::isInCheck(bool defenderColour) {
    // Get king's location
    int kingFR[2];
    getDefenderKingLoc(defenderColour, kingFR);

    // Go through whole board
    for (int f = 0; f < FILES; f++) {
        for (int r = 0; r < RANKS; r++) {

            // Skip empty squares
            if (square[f][r] != NULL) {
                ChessPiece* attacker = square[f][r];
                bool attackerColour = attacker->isPieceWhite();

                // Consider only enemy pieces
                if (attackerColour != defenderColour) {

                    // If any enemy piece can validly attack king, return true
                    if (attacker->isValidMove(kingFR, square)) return true;
                }
            }
        }
    }
    return false;
}

void ChessBoard::getDefenderKingLoc(bool ownColour, int goal[2]) {

    // Go through every square
    for (int f = 0; f < FILES; f++) {
        for (int r = 0; r < RANKS; r++) {

            // If piece on square
            if (square[f][r] != NULL) {
                const char* pieceName = square[f][r]->getPieceType();
                bool pieceColour = square[f][r]->isPieceWhite();

                // If piece is own king, get location and return
                if (!strcmp(pieceName, "King") && pieceColour == ownColour) {
                    goal[0] = f;
                    goal[1] = r;
                    return;
                }
            }
        }
    }
}

bool ChessBoard::playerHasLegalMove(bool playerColour) {
    // If enemy has no other possible moves to make that would be legal
    // (aka valid move AND wouldn't result in check), then checkmate

    // Check every square
    for (int f = 0; f < FILES; f++) {
        for (int r = 0; r < RANKS; r++) {

            // Consider any square with a piece on it...
            if (square[f][r] != NULL) {

                ChessPiece* piece = square[f][r];
                bool pieceColour = piece->isPieceWhite();
                int fromFR[] = {f, r};

                // Consider only pieces of the player's colour...
                if (pieceColour == playerColour) {

                    for (int x = 0; x < FILES; x++) {
                        for (int y = 0; y < RANKS; y++) {
                            int toFR[] = {x, y};

                            // If so, NO CHECKMATE
                            // Can piece move to ANY other square & avoid check?
                            if (piece->isValidMove(toFR, square) &&
                                safeFromSelfCheck(fromFR, toFR)) {
                                return true;
                            }
                        }
                    }
                }

            }
        }
    }
    // If not, then CHECKMATE OR STALEMATE
    return false;
}

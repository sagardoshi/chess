/*
METADATA
Name: Sagar Doshi
Date: 25 February 2018
Title: Chess
Class: Object Oriented Programming & Design
Course: MSc Computing Science
University: Imperial College London
*/

#include "../inc/ChessBoard.h"

#include <iostream>
using namespace std;

int main() {

    cout << "===========================" << endl;
    cout << "Testing the Chess Engine" << endl;
    cout << "===========================" << endl;
    cout << endl;

    ChessBoard cb;
    cout << endl;

    cb.submitMove("B2", "B4");
    cout << endl;

    cb.submitMove("F7", "F6");
    cout << endl;

    cb.submitMove("B1", "C3");
    cout << endl;
    cb.submitMove("E7", "E5");
    cout << endl;

    cb.submitMove("C3", "B5");
    cout << endl;

    cb.submitMove("F8", "C5");
    cout << endl;

    cb.submitMove("A2", "A4");
    cout << endl;
    cb.submitMove("C5", "D4");
    cout << endl;

    cb.submitMove("E2", "E3");
    cout << endl;
    cb.submitMove("H7", "H5");
    cout << endl;

    cb.submitMove("C2", "C4");
    cout << endl;
    cb.submitMove("D4", "C3");
    cout << endl;

    cb.submitMove("D2", "D3"); // results in self-check!
    cout << endl;
    cb.submitMove("D2", "C3"); // first capture
    cout << endl;
    cb.submitMove("B8", "C6");
    cout << endl;

    cb.submitMove("B5", "D6");
    cout << endl;
    cb.submitMove("E8", "E7");
    cout << endl;



    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cout << endl;

    cb.submitMove("E2", "E4");
    cb.submitMove("E7", "E6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << endl;

    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << endl;

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << endl;

    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << endl;

    cb.submitMove("C1", "A3");
    cb.submitMove("B8", "D7");
    cout << endl;

    cb.submitMove("D1", "E2");
    cb.submitMove("D5", "E4");
    cout << endl;

    cb.submitMove("D3", "E4");
    cb.submitMove("G8", "F6");
    cout << endl;

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << endl;

    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << endl;

    cb.submitMove("D3", "G6");
    cout << endl;

    return 0;
}

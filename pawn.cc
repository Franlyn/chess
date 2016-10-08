//i
//  pawn.cc
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "pawn.h"
using namespace std;


// the ctor
Pawn::Pawn(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c) : ChessPiece(type, colour, theBoard, r, c), firstmove{true}, secondmove{false} {}


// update possibleMoves, possibleAttacks and possibleChecks
// special case: en passant
// two updates for other chess pieces:
// 1. if this is not my secondmove, then check whether I am a would-be attacking pawn.
//    if I am, then update the would_be attacked pwawn's possibleMoves
// 2. if this is my secondmove, then update the would-be attacking pawn's possibleAttacks

void Pawn::update(vector<vector<Square>> &theBoard) {
 
    // clear possibleMoves & possibleAttacks
    // (note: possibleChecks is cleared from its own update function)
    possibleMoves.clear();
    possibleAttacks.clear();
    
    int r = this->row;
    int c = this->col;
   
    if (this->colour == 'W') {

        // update possibleMoves & possibleAttacks in 3 directions:
        // up(standard or two-square), up right(capturing), up left(capturing)

        if (this->firstmove && (r+2 <= 7) && theBoard[r+2][c].isEmpty()) {// up (two-square)
            possibleMoves.emplace_back(make_pair<int, int>(int(r+2), int(c)));
        }

	if ((r+1 <= 7) && (theBoard[r+1][c].isEmpty())) {// up (standard)
            possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c)));
        }

        if ((r+1 <= 7) && (c+1 <= 7) && (!theBoard[r+1][c+1].isEmpty())) {// up right
            if (theBoard[r+1][c+1].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c+1)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c+1)));
            }
        }

        if ((r+1 <= 7) && (c-1 >= 0) && (!theBoard[r+1][c-1].isEmpty())) {// up left
            if (theBoard[r+1][c-1].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
            }
        }

        // special case: en passant
        if ((r+2 <= 7) && (c+1 <= 7) && !theBoard[r+2][c+1].isEmpty() &&
            (theBoard[r+2][c+1].getColour() != this->colour) && (theBoard[r+2][c+1].getType() == 'P')) {
        	theBoard[r+2][c+1].addMove(r, c+1);
        }

        if ((r+2 <= 7) && (c-1 >= 0) && !theBoard[r+2][c-1].isEmpty() &&
            (theBoard[r+2][c-1].getColour() != this->colour) && (theBoard[r+2][c-1].getType() == 'P')) {
        	theBoard[r+2][c-1].addMove(r, c-1);
        }
        
	if ((c+1 <= 7) && !theBoard[r][c+1].isEmpty() && theBoard[r][c+1].getType() == 'P' &&
	    (theBoard[r][c+1].getColour() != this->colour) && theBoard[r][c+1].secondMove()) {
		possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c+1)));
		possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c+1)));
	}

	if ((c-1 >= 0) && !theBoard[r][c-1].isEmpty() && theBoard[r][c-1].getType() == 'P' &&
            (theBoard[r][c-1].getColour() != this->colour) && theBoard[r][c-1].secondMove()) {
                possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
                possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c-1)));
        }
    }
    
    else if (this->colour == 'B') {

        // update possibleMoves & possibleAttacks in 3 directions:
        // down(standard or two-square), down right(capturing), down left(capturing)

	if (this->firstmove && (r-2 >= 0) && theBoard[r-2][c].isEmpty()) {// down (two-square)
            possibleMoves.emplace_back(make_pair<int, int>(int(r-2), int(c)));
        }

        if ((r-1 >= 0) && (theBoard[r-1][c].isEmpty())) { // down
            possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c)));
        }

        if ((r-1 >= 0) && (c+1 <= 7) && (!theBoard[r-1][c+1].isEmpty())) {// down right
            if (theBoard[r-1][c+1].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
            }
        }

        if ((r-1 >= 0) && (c-1 >= 0) && (!theBoard[r-1][c-1].isEmpty())) {// down left
            if (theBoard[r-1][c-1].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
            }
        }
 
        // special case: en passant
        if ((r-2 >= 0) && (c+1 <= 7) && !theBoard[r-2][c+1].isEmpty() &&
            (theBoard[r-2][c+1].getColour() != this->colour) && (theBoard[r-2][c+1].getType() == 'P')) {
        	theBoard[r-2][c+1].addMove(r, c+1);
        }
        if ((r-2 >= 0) && (c-1 >= 0) && !theBoard[r-2][c-1].isEmpty() &&
            (theBoard[r-2][c-1].getColour() != this->colour) && (theBoard[r-2][c-1].getType() == 'P')) {
        	theBoard[r-2][c-1].addMove(r, c-1);
        }

	if ((c+1 <= 7) && !theBoard[r][c+1].isEmpty() && theBoard[r][c+1].getType() == 'P' &&
            (theBoard[r][c+1].getColour() != this->colour) && theBoard[r][c+1].secondMove()) {
                possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
                possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c+1)));
        }

        if ((c-1 >= 0) && !theBoard[r][c-1].isEmpty() && theBoard[r][c-1].getType() == 'P' &&
            (theBoard[r][c-1].getColour() != this->colour) && theBoard[r][c-1].secondMove()) {
                possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
                possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c-1)));
        }
    }
    
    // update possibleChecks
    update_possibleChecks();
}

// check whether should put (r, c) into possibleChecks
bool Pawn::canCheck(const int r, const int c) {
    if (r+1 <= 7 && !myBoard[r+1][c].isEmpty() && // up
        myBoard[r+1][c].getType() == 'K' && myBoard[r+1][c].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c+1 <= 7 && !myBoard[r+1][c+1].isEmpty() && // up right
        myBoard[r+1][c+1].getType() == 'k' && myBoard[r+1][c+1].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c-1 >= 0 && !myBoard[r+1][c-1].isEmpty() && // up left
        myBoard[r+1][c-1].getType() == 'k' && myBoard[r+1][c-1].getColour() != this->colour)
        return true;
    return false; // if non if above conditions returned, then finally return false
}


// return the value of firstmove
bool Pawn::isFirstMove() { return this->firstmove; }

// return the value of secondmove
bool Pawn::isSecondMove() {return this->secondmove; }

// set this pawn as not firstmove
void Pawn::setNotFirst() { this->firstmove = false; } 

// set this pawn as secondmove
void Pawn::setSecond() { this->secondmove = true; }

// set this pawn as not secondmove
void Pawn::setNotSecond() { this->secondmove = false; }

// the dtor
Pawn::~Pawn() {}

//
//  king.cc
//  Chess
//
//  Created by Minglu Li on 7/15/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "king.h"
using namespace std;


// the ctor
King::King(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c): ChessPiece(type, colour, theBoard, r, c), firstmove{true} {}


// update possibleMoves, possibleAttacks, and possibleChecks
void King::update(vector<vector<Square>> &theBoard) {
    
    // clear possibleMoves & possibleAttacks
    // (note: possibleChecks is cleared from its own update function)
    possibleMoves.clear();
    possibleAttacks.clear();
    
    int r = this->row;
    int c = this->col;
    
    // update possibleMoves & possibleAttacks in 8 directions:
    // up, up right, right, down right, down, down left, left, up left

    // up
    if ((r+1 <= 7) && (!theBoard[r+1][c].isEmpty())) {
        if (theBoard[r+1][c].getColour() != this->colour && !isInCheck(r+1, c)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c)));
        }
    }
    if ((r+1 <= 7) && (theBoard[r+1][c].isEmpty()) && !isInCheck(r+1, c)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c)));
    }
    
    // up right
    if ((r+1 <= 7) && (c+1 <= 7) && (!theBoard[r+1][c+1].isEmpty())) {
        if (theBoard[r+1][c+1].getColour() != this->colour && !isInCheck(r+1, c+1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c+1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c+1)));
        }
    }
    if ((r+1 <= 7) && (c+1 <= 7) && (theBoard[r+1][c+1].isEmpty()) && !isInCheck(r+1, c+1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+1), (c+1)));
    }
    
    // right
    if ((c+1 <= 7) && (!theBoard[r][c+1].isEmpty())) {
        if (theBoard[r][c+1].getColour() != this->colour && !isInCheck(r, c+1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c+1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c+1)));
        }
    }
    if ((c+1 <= 7) && (theBoard[r][c+1].isEmpty()) && !isInCheck(r, c+1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c+1)));
    }
    
    // down right
    if ((r-1 >= 0) && (c+1 <= 7) && (!theBoard[r-1][c+1].isEmpty())) {
        if (theBoard[r-1][c+1].getColour() != this->colour && !isInCheck(r-1, c+1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
        }
    }
    if ((r-1 >= 0) && (c+1 <= 7) && (theBoard[r-1][c+1].isEmpty()) && !isInCheck(r-1, c+1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c+1)));
    }
    
    // down
    if ((r-1 >= 0) && (!theBoard[r-1][c].isEmpty())) {
        if (theBoard[r-1][c].getColour() != this->colour && !isInCheck(r-1, c)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c)));
        }
    }
    if ((r-1 >= 0) && (theBoard[r-1][c].isEmpty()) && !isInCheck(r-1, c)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c)));
    }
    
    // down left
    if ((r-1 >= 0) && (c-1 >= 0) && (!theBoard[r-1][c-1].isEmpty())) {
        if (theBoard[r-1][c-1].getColour() != this->colour && !isInCheck(r-1, c-1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
        }
    }
    if ((r-1 >= 0) && (c-1 >= 0) && (theBoard[r-1][c-1].isEmpty()) && !isInCheck(r-1, c-1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c-1)));
    }
    
    // left
    if ((c-1 >= 0) && (!theBoard[r][c-1].isEmpty())) {
        if (theBoard[r][c+1].getColour() != this->colour && !isInCheck(r, c-1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c-1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c-1)));
        }
    }
    if ((c-1 >= 0) && (theBoard[r][c-1].isEmpty()) && !isInCheck(r, c-1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c-1)));
    }
    
    // up left
    if ((r+1 <= 7) && (c-1 >= 0) && (!theBoard[r+1][c-1].isEmpty())) {
        if (theBoard[r+1][c-1].getColour() != this->colour && !isInCheck(r+1, c-1)) {
            possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
            possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
        }
    }
    if ((r+1 <= 7) && (c-1 >= 0) && (theBoard[r+1][c-1].isEmpty()) && !isInCheck(r+1, c-1)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c-1)));
    }
    
    // special case: castling, only occurs when this is the King's first move
    if (this->firstmove) {
        //this->firstmove = false;
        bool legal = true;
    
        if (this->colour == 'W') {
            // check whether move to (0, 2) is a valid castling
            if ((!theBoard[0][0].isEmpty()) &&(theBoard[0][0].getType() == 'R')) {
                for (int i = 3; i > 0; i--) {
                    if (!theBoard[0][i].isEmpty() || King::isInCheck(0, i)) legal = false;
                }
                if (legal && theBoard[0][0].firstMove()) {
                    possibleMoves.emplace_back(make_pair<int, int>(0, 2));
                }
            }
            // check whether move to (0, 6) is a valid castling
            legal = true; // set back to true
            if ((!theBoard[0][7].isEmpty()) &&(theBoard[0][7].getType() == 'R')) {
                for (int i = 5; i < 7; i++) {
                    if (!theBoard[0][i].isEmpty() || King::isInCheck(0, i)) legal = false;
                }
                if (legal && theBoard[0][7].firstMove()) {
                    possibleMoves.emplace_back(make_pair<int, int>(0, 6));
                }
            }
        }
        
        else if (this->colour == 'B') {
            // check whether move to (7, 2) is a valid castling
            if ((!theBoard[7][0].isEmpty()) &&(theBoard[7][0].getType() == 'R')) {
                for (int i = 3; i > 0; i--) {
                    if (!theBoard[7][i].isEmpty() || King::isInCheck(7, i)) legal = false;
                }
                if (legal && theBoard[0][0].firstMove()) {
                    possibleMoves.emplace_back(make_pair<int, int>(7, 2));
                }
            }
            // check whether move to (7, 6) is a valid castling
            legal = true; // set back to true
            if ((!theBoard[7][7].isEmpty()) &&(theBoard[7][7].getType() == 'R')) {
                for (int i = 5; i < 7; i++) {
                    if (!theBoard[7][i].isEmpty() || King::isInCheck(7, i)) legal = false;
                }
                if (legal && theBoard[7][7].firstMove()) {
                    possibleMoves.emplace_back(make_pair<int, int>(7, 6));
                }
            }
        }
    }
    
    // update possibleChecks
    update_possibleChecks();
}


// whether the move to (r, c) could put me in check
bool King::isInCheck(const int r, const int c) {
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (!myBoard[i][j].isEmpty() && myBoard[i][j].canAttack(r, c)) return true;
        }
    }
    return false;
}

// check whether should put (r, c) into possibleChecks
bool King::canCheck(const int r, const int c) {
    if (r+1 <= 7 && !myBoard[r+1][c].isEmpty() && // up
        myBoard[r+1][c].getType() == 'K' && myBoard[r+1][c].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c+1 <= 7 && !myBoard[r+1][c+1].isEmpty() && // up right
        myBoard[r+1][c+1].getType() == 'k' && myBoard[r+1][c+1].getColour() != this->colour)
        return true;
    if (c+1 <= 7 && !myBoard[r][c+1].isEmpty() && // right
        myBoard[r][c+1].getType() == 'k' && myBoard[r][c+1].getColour() != this->colour)
        return true;
    if (r-1 >= 0 && c+1 <= 7 && !myBoard[r-1][c+1].isEmpty() && // down right
        myBoard[r-1][c+1].getType() == 'k' && myBoard[r-1][c+1].getColour() != this->colour)
        return true;
    if (r-1 >= 0 && !myBoard[r-1][c].isEmpty() && // down
        myBoard[r-1][c].getType() == 'K' && myBoard[r-1][c].getColour() != this->colour)
        return true;
    if (r-1 >= 0 && c-1 >= 0 && !myBoard[r-1][c-1].isEmpty() && // down left
        myBoard[r-1][c-1].getType() == 'k' && myBoard[r-1][c-1].getColour() != this->colour)
        return true;
    if (c-1 >= 0 && !myBoard[r][c-1].isEmpty() && // left
        myBoard[r][c-1].getType() == 'k' && myBoard[r][c-1].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c-1 >= 0 && !myBoard[r+1][c-1].isEmpty() && // up left
        myBoard[r+1][c-1].getType() == 'k' && myBoard[r+1][c-1].getColour() != this->colour)
        return true;
    return false; // if non if above conditions returned, then finally return false
}


// return the value of firstmove
bool King::isFirstMove() { return this->firstmove; }


// set this King as not firstmove
void King::setNotFirst() { this->firstmove = false; }


// the dtor
King::~King() {}

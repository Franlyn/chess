//
//  bishop.cc
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "bishop.h"
using namespace std;

// the ctor
Bishop::Bishop(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c) : ChessPiece(type, colour, theBoard, r, c) {}


// update possibleMoves, possibleAttacks and possibleChecks
void Bishop::update(vector<vector<Square>> &theBoard) {
    
    // clear possibleMoves & possibleAttacks
    // (note: posibleChecks is cleared from its own update function)
    possibleMoves.clear();
    possibleAttacks.clear();
    
    int r = this->row;
    int c = this->col;
    
    // update possibleMoves & possibleAttacks in 4 diagonal directions:
    // up right, down right, down left, up left
    for (int i = 1; r+i <= 7 && c+i <= 7; i++) { // up right
        if (!theBoard[r+i][c+i].isEmpty()) {
            if (theBoard[r+i][c+i].getColour() != this->getColour()) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
        }
    }
    
    for (int i = 1; r-i >= 0 && c+i <= 7; i++) { // down right
        if (!theBoard[r-i][c+i].isEmpty()) {
            if (theBoard[r-i][c+i].getColour() != this->getColour()) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
        }
    }
    
    for (int i = 1; r-i >= 0 && c-i >= 0; i++) { // down left
        if (!theBoard[r-i][c-i].isEmpty()) {
            if (theBoard[r-i][c-i].getColour() != this->getColour()) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
        }
    }
    
    for (int i = 1; r+i <= 7 && c-i >= 0; i++) { // up left
        if (!theBoard[r+i][c-i].isEmpty()) {
            if (theBoard[r+i][c-i].getColour() != this->getColour()) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+i), int(c-i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c-i)));
            }
            break;
        }
        else{
            possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c-i)));
        }
    }
    
    // update possibleChecks
    update_possibleChecks();
}


// check whether should put (r, c) into possibleChecks
bool Bishop::canCheck(const int r, const int c) {
    for (int i = 1; r+i <= 7 && c+i <= 7; i++) { // up right
        if (myBoard[r+i][c+i].isEmpty()) continue;
        else if (myBoard[r+i][c+i].getType() == 'K' && myBoard[r+i][c+i].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r-i >= 0 && c+i <= 7; i++) { // down right
        if (myBoard[r-i][c+i].isEmpty()) continue;
        else if (myBoard[r-i][c+i].getType() == 'K' && myBoard[r-i][c+i].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r-i >= 0 && c-i >= 0; i++) { // down left
        if (myBoard[r-i][c-i].isEmpty()) continue;
        else if (myBoard[r-i][c-i].getType() == 'K' && myBoard[r-i][c-i].getColour() != this->colour)
            return true;
        else break;
    }
    
    for (int i = 1; r+i <= 7 && c-i >= 0; i++) { // up left
        if (myBoard[r+i][c-i].isEmpty()) continue;
        else if (myBoard[r+i][c-i].getType() == 'K' && myBoard[r+i][c-i].getColour() != this->colour)
            return true;
        else break;
    }
    
    return false; // if non of above conditions returned, then finally return false
}


// the dtor
Bishop::~Bishop() {}

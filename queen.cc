//
//  queen.cc
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "queen.h"
using namespace std;

// the ctor
Queen::Queen(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c) : ChessPiece(type, colour, theBoard, r, c) {}


// update possibleMoves, possibleAttacks, and possibleChecks
void Queen::update(vector<vector<Square>> &theBoard) {
    
    // clear possibleMoves & possibleAttacks
    // (note: possibleChecks is cleared from its own update function)
    possibleMoves.clear();
    possibleAttacks.clear();
    
    // update possibleMoves & possibleAttacks in 8 possible directions:
    // up, up right, right, down right, down, down left, left, up left
    
    int r = this->row;
    int c = this->col;
    
    for (int i = 1; r+i <= 7; i++) { // up
        if (!theBoard[r+i][c].isEmpty()) {
            if (theBoard[r+i][c].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+i), int(c)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c)));
        }
    }
    
    for (int i = 1; r+i <= 7 && c+i <= 7; i++) { // up right
        if (!theBoard[r+i][c+i].isEmpty()) {
            if (theBoard[r+i][c+i].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r+i), int(c+i)));
        }
    }
    
    for (int i = 1; c+i <= 7; i++) { // right
        if (!theBoard[r][c+i].isEmpty()) {
            if (theBoard[r][c+i].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c+i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c+i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c+i)));
        }
    }
    
    for (int i = 1; r-i >= 0 && c+i <= 7; i++) { // down right
        if (!theBoard[r-i][c+i].isEmpty()) {
            if (theBoard[r-i][c+i].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c+i)));
        }
    }
    
    for (int i = 1; r-i >= 0; i++) { // down
        if (!theBoard[r-i][c].isEmpty()) {
            if (theBoard[r-i][c].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-i), int(c)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c)));
        }
    }
    
    for (int i = 1; r-i >= 0 && c-i >= 0; i++) { // down left
        if (!theBoard[r-i][c-i].isEmpty()) {
            if (theBoard[r-i][c-i].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r-i), int(c-i)));
        }
    }
    for (int i = 1; c-i >= 0; i++) { // left
        if (!theBoard[r][c-i].isEmpty()) {
            if (theBoard[r][c-i].getColour() != this->colour) {
                possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c-i)));
                possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c-i)));
            }
            break;
        }
        else {
            possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c-i)));
        }
    }
    
    for (int i = 1; r+i <= 7 && c-i >= 0; i++) { // up left
        if (!theBoard[r+i][c-i].isEmpty()) {
            if (theBoard[r+i][c-i].getColour() != this->colour) {
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
bool Queen::canCheck(const int r, const int c) {
    for (int i = 1; r+i <= 7; i++) { // up
        if (myBoard[r+i][c].isEmpty()) continue;
        else if (myBoard[r+i][c].getType() == 'K' && myBoard[r+i][c].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r+i <= 7 && c+i <= 7; i++) { // up right
        if (myBoard[r+i][c+i].isEmpty()) continue;
        else if (myBoard[r+i][c+i].getType() == 'K' && myBoard[r+i][c+i].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; c+i <= 7; i++) { // right
        if (myBoard[r][c+i].isEmpty()) continue;
        else if (myBoard[r][c+i].getType() == 'K' && myBoard[r][c+i].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r-i >= 0 && c+i <= 7; i++) { // down right
        if (myBoard[r-i][c+i].isEmpty()) continue;
        else if (myBoard[r-i][c+i].getType() == 'K' && myBoard[r-i][c+i].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r-i >= 0; i++) { // down
        if (myBoard[r-i][c].isEmpty()) continue;
        else if (myBoard[r-i][c].getType() == 'K' && myBoard[r-i][c].getColour() != this->colour)
            return true;
        else break;
    }
    for (int i = 1; r-i >= 0 && c-i >= 0; i++) { // down left
        if (myBoard[r-i][c-i].isEmpty()) continue;
        else if (myBoard[r-i][c-i].getType() == 'K' && myBoard[r-i][c-i].getColour() != this->colour)
            return true;
        else break;
    }
    
    for (int i = 1; c-i >= 0; i++) { // left
        if (myBoard[r][c-i].isEmpty()) continue;
        else if (myBoard[r][c-i].getType() == 'K' && myBoard[r][c-i].getColour() != this->colour)
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
Queen::~Queen() {}

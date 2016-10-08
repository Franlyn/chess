//
//  knight.cc
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "knight.h"
using namespace std;


// the ctor
Knight::Knight(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c): ChessPiece(type, colour, theBoard, r, c) {}


// update possibleMoves, possibleAttacks and possibleChecks
void Knight::update(vector<vector<Square>> &theBoard) {
    // clear possibleMoves & possibleAttacks
    // (note: possibleChecks is cleared from its own update function)
    possibleMoves.clear();
    possibleAttacks.clear();
    
    int r = this->row;
    int c = this->col;
    
    // check and update Knight's possibleMoves & possibleAttacks
    if (r+2 <= 7 && c+1 <= 7 && (theBoard[r+2][c+1].isEmpty() || theBoard[r+2][c+1].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+2), int(c+1)));
        if (!theBoard[r+2][c+1].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r+2), int(c+1)));
    }
    
    if (r+2 <= 7 && c-1 >= 0 && (theBoard[r+2][c-1].isEmpty() || theBoard[r+2][c-1].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+2), int(c-1)));
        if (!theBoard[r+2][c-1].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r+2), int(c-1)));
    }
    
    if (r-2 >= 0 && c+1 <= 7 && (theBoard[r-2][c+1].isEmpty() || theBoard[r-2][c+1].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-2), int(c+1)));
        if (!theBoard[r-2][c+1].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r-2), int(c+1)));
    }
    
    if (r-2 >= 0 && c-1 >= 0 && (theBoard[r-2][c-1].isEmpty() || theBoard[r-2][c-1].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-2), int(c-1)));
        if (!theBoard[r-2][c-1].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r-2), int(c-1)));
    }
    
    if (r+1 <= 7 && c+2 <= 7 && (theBoard[r+1][c+2].isEmpty() || theBoard[r+1][c+2].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c+2)));
        if (!theBoard[r+1][c+2].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c+2)));
    }
    
    if (r+1 <= 7 && c-2 >= 0 && (theBoard[r+1][c-2].isEmpty() || theBoard[r+1][c-2].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r+1), int(c-2)));
        if (!theBoard[r+1][c-2].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r+1), int(c-2)));
    }
    
    if (r-1 >= 0 && c+2 <= 7 && (theBoard[r-1][c+2].isEmpty() || theBoard[r-1][c+2].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c+2)));
        if (!theBoard[r-1][c+2].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c+2)));
    }
    
    if (r-1 >= 0 && c-2 >= 0 && (theBoard[r-1][c-2].isEmpty() || theBoard[r-1][c-2].getColour() != this->colour)) {
        possibleMoves.emplace_back(make_pair<int, int>(int(r-1), int(c-2)));
        if (!theBoard[r-1][c-2].isEmpty()) possibleAttacks.emplace_back(make_pair<int, int>(int(r-1), int(c-2)));
    }
    
    // update possibleChecks
    update_possibleChecks();
}


// check whether should put (r, c) into possibleChecks
bool Knight::canCheck(const int r, const int c) {
    if (r+2 <= 7 && c+1 <= 7 && !myBoard[r+2][c+1].isEmpty() &&
        myBoard[r+2][c+1].getType() == 'K' && myBoard[r+2][c+1].getColour() != this->colour)
        return true;
    if (r+2 <= 7 && c-1 >= 0 && !myBoard[r+2][c-1].isEmpty() &&
        myBoard[r+2][c-1].getType() == 'K' && myBoard[r+2][c-1].getColour() != this->colour)
        return true;
    if (r-2 >= 0 && c+1 <= 7 && !myBoard[r-2][c+1].isEmpty() &&
        myBoard[r-2][c+1].getType() == 'K' && myBoard[r-2][c+1].getColour() != this->colour)
        return true;
    if (r-2 >= 0 && c-1 >= 0 && !myBoard[r-2][c-1].isEmpty() &&
        myBoard[r-2][c-1].getType() == 'K' && myBoard[r-2][c-1].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c+2 <= 7 && !myBoard[r+1][c+2].isEmpty() &&
        myBoard[r+1][c+2].getType() == 'K' && myBoard[r+1][c+2].getColour() != this->colour)
        return true;
    if (r+1 <= 7 && c-2 >= 0 && !myBoard[r+1][c-2].isEmpty() &&
        myBoard[r+1][c-2].getType() == 'K' && myBoard[r+1][c-2].getColour() != this->colour)
        return true;
    if (r-1 >= 0 && c+2 <= 7 && !myBoard[r-1][c+2].isEmpty() &&
        myBoard[r-1][c+2].getType() == 'K' && myBoard[r-1][c+2].getColour() != this->colour)
        return true;
    if (r-1 >= 0 && c-2 >= 0 && !myBoard[r-1][c-2].isEmpty() &&
        myBoard[r-1][c-2].getType() == 'K' && myBoard[r-1][c-2].getColour() != this->colour)
        return true;
    return false; // if non if above conditions returned, then finally return false
}


// the dtor
Knight::~Knight() {}

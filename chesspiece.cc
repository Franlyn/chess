//
//  chesspiece.cc
//  Chess
//
//  Created by Minglu Li on 7/15/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#include "chesspiece.h"
using namespace std;

// the ctor
ChessPiece::ChessPiece(const char type, const char colour, vector<vector<Square>> &theBoard, const int r, const int c) : type{type}, colour{colour}, myBoard{theBoard} {
    this->row = r;
    this->col = c;
}


// get the current chesspiece's type {K, Q, B, R, N, P}
char ChessPiece::getType() { return this->type; }


// get the current chesspiece's colour {W, B}
char ChessPiece::getColour() { return this->colour; }


// chear & update possibleChecks. This function is called in function update()
void ChessPiece::update_possibleChecks() {
    possibleChecks.clear();
    for (auto movePoint : possibleMoves) {
        if (this->canCheck(movePoint.first, movePoint.second)) {
            possibleChecks.emplace_back(movePoint);
        }
    }
}


// check whether square(r, c) is in my possibleMoves
bool ChessPiece::inPossibleMoves(const int r, const int c) {
    pair<int, int> coor = make_pair(r, c);
    for (auto movePoint : possibleMoves) {
        if ( coor == movePoint) return true;
    }
    return false;
}

// check whether square(r, c) is in my possibleAttacks
bool ChessPiece::inPossibleAttacks(const int r, const int c) {
    pair<int, int> coor = make_pair(r, c);
    for (auto attackPoint : possibleAttacks) {
        if (coor == attackPoint) return true;
    }
    return false;
}


// whether (r, c) is capture-free (not in any chess piece's possibleAttacks)
bool ChessPiece::captureFree(const int r, const int c) {
  for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (!myBoard[i][j].isEmpty() && myBoard[i][j].canAttack(r, c)) return false;
        }
    }
    return true;
}


// return the size of possibleMoves
int ChessPiece::sizeMoves() { return possibleMoves.size(); }


// return the size of possibleAttacks
int ChessPiece::sizeAttacks() { return possibleAttacks.size(); }


// return the size of possibleChecks
int ChessPiece::sizeChecks() { return possibleChecks.size(); }


// add (r, c) to possibleMoves
void ChessPiece::addPossibleMove(const int r, const int c) {
    if (!inPossibleMoves(r, c)) possibleMoves.emplace_back(make_pair<int, int>(int(r), int(c)));
}

// add (r, c) to possibleAttacks
void ChessPiece::addPossibleAttack(const int r, const int c) {
    if (!inPossibleAttacks(r, c)) possibleAttacks.emplace_back(make_pair<int, int>(int(r), int(c)));
}

// get the pair in possibleMoves at rand position
pair<int, int> ChessPiece::getMove(int rand) { return possibleMoves[rand]; }


// get the pair in possibleAttacks at rand position
pair<int, int> ChessPiece::getAttack(int rand) { return possibleAttacks[rand]; }


// get the pair in possibleChecks at rand position
pair<int, int> ChessPiece::getCheck(int rand) { return possibleChecks[rand]; }


// set the piece's coordinates
void ChessPiece::setPieceCoords(const int r, const int c) {
    this->row = r;
    this->col = c;
}


bool ChessPiece::isInCheck(const int r, const int c) { return false; }

bool ChessPiece::isFirstMove() { return false; }

bool ChessPiece::isSecondMove() {return false; }

void ChessPiece::setSecond() {}

void ChessPiece::setNotSecond() {}

void ChessPiece::setNotFirst() {}

// the dtor
ChessPiece::~ChessPiece() {}

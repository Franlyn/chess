//
//  chesspiece.h
//  Chess
//
//  Created by Minglu Li on 7/15/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//


#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include <iostream>
#include <vector>
#include <utility>
#include "board.h"
#include "square.h"
class Board;
class Square;

class ChessPiece {
    virtual bool canCheck(const int r, const int c) = 0; // check whether should put (r, c) in possibleChecks

  protected:
    const char type; // possible types: {K, Q, B, R, N, P}
    const char colour; // for two_hand game, possible colours: {W, B}
    int row = 0; // row position in theBoard
    int col = 0; // column position in theBoard
    std::vector<std::vector<Square>> &myBoard;
    std::vector<std::pair<int, int>> possibleMoves;
    std::vector<std::pair<int, int>> possibleAttacks;
    std::vector<std::pair<int, int>> possibleChecks;
    
    void update_possibleChecks(); // called by update()
    
  public:
    
    ChessPiece(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    virtual void update(std::vector<std::vector<Square>> &theBoard) = 0; // update possibleMoves, possibleAttacks, and possibleChecks
    
    char getType(); 
    char getColour(); 
    bool inPossibleMoves(const int r, const int c);
    bool inPossibleAttacks(const int r, const int c);
    bool captureFree(const int r, const int c);
    int sizeMoves(); // return the size of possibleMoves
    int sizeAttacks(); // return the size of possibleAttacks
    int sizeChecks(); // return the size of possibleChecks
    void addPossibleMove(const int r, const int c); // add (r, c) to possibleMoves
    void addPossibleAttack(const int r, const int c); // add (r, c) to possibleAttacks
    std::pair<int, int> getMove(int rand); // get coordinates in possibleMoves
    std::pair<int, int> getAttack(int rand); // get coordinates in possibleAttacks
    std::pair<int, int> getCheck(int rand); // get coordinates in possibleChecks
    void setPieceCoords(const int r, const int c);

    virtual bool isInCheck(const int r, const int c);// for King
    virtual bool isFirstMove();// for Pawn & Rook & King
    virtual void setNotFirst();// for Pawn & Rook & King
    virtual bool isSecondMove(); // for Pawn    
    virtual void setSecond(); // for Pawn
    virtual void setNotSecond(); // for Pawn

    virtual ~ChessPiece() = 0;
    
};


#endif /* chesspiece.h */

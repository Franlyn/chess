//
//  pawn.h
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#ifndef __PAWN_H__
#define __PAWN_H__

#include <iostream>
#include "chesspiece.h"

class Pawn : public ChessPiece {
    bool firstmove; // default true
    bool secondmove; // default false
    bool canCheck(const int r, const int c) override;
    
  public:
    Pawn(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    void update(std::vector<std::vector<Square>> &theBoard) override;

    void setSecond() override;    
    bool isFirstMove() override;
    void setNotFirst() override;
    bool isSecondMove() override;
    void setNotSecond() override;
    ~Pawn();
    
};

#endif /* pawn.h */

//
//  king.h
//  Chess
//
//  Created by Minglu Li on 7/15/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#ifndef __KING_H__
#define __KING_H__

#include <iostream>
#include "chesspiece.h"

class King : public ChessPiece {
    bool firstmove; // default to true
    bool canCheck(const int r, const int c) override;
    
  public:
    King(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    void update(std::vector<std::vector<Square>> &theBoard) override;
    bool isInCheck(const int r, const int c) override; // check whether the move to (r, c) could put me in check
    bool isFirstMove() override; 
    void setNotFirst() override;
    ~King();
    
};

#endif /* king.h */

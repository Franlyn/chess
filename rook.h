//
//  rook.h
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#ifndef __ROOK_H__
#define __ROOK_H__

#include <iostream>
#include "chesspiece.h"

class Rook : public ChessPiece {
    bool firstmove; // default true
    bool canCheck(const int r, const int c) override;

  public:
    Rook(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    void update(std::vector<std::vector<Square>> &theBoard) override;
    bool isFirstMove() override;
    void setNotFirst() override;
    ~Rook();
    
};

#endif /* rook.h */

//
//  bishop.h
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#ifndef __BISHOP_H__
#define __BISHOP_H__

#include <iostream>
#include "chesspiece.h"

class Bishop : public ChessPiece {
    bool canCheck(const int r, const int c) override;

  public:
    Bishop(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    void update(std::vector<std::vector<Square>> &theBoard) override;
    ~Bishop();
};

#endif /* bishop.h */

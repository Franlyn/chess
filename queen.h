//
//  queen.h
//  Chess
//
//  Created by Minglu Li on 7/17/16.
//  Copyright © 2016 Minglu Li. All rights reserved.
//

#ifndef __QUEEN_H__
#define __QUEEN_H__

#include <iostream>
#include "chesspiece.h"


class Queen : public ChessPiece {
    bool canCheck(const int r, const int c) override;

  public:
    Queen(const char type, const char colour, std::vector<std::vector<Square>> &theBoard, const int r, const int c);
    void update(std::vector<std::vector<Square>> &theBoard) override;
    ~Queen();
    
};

#endif /* queen.h */

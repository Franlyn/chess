#ifndef _COMPUTERLEVEL_H_
#define _COMPUTERLEVEL_H_
#include <iostream>
#include <vector>
#include <utility>
#include "board.h"
#include "player.h"
#include "computer.h"

class Level1: public Computer {
	//char playerType; // either 'H' (human player) or 'C' (computer player)
	//char colour; // either 'W' (white) or 'B' (black)
  public:
  	Level1(char colour, char pt);
  	//char getPlayerType();
  	//char getColourTurn();
  	int cMove(Board &b) override;
  	//pair<int, char> moveFrom() override;
  	//pair<int, char> moveTo() override;
};


class Level2: public Computer {
  public:
  	Level2(char colour,char pt);
  	int cMove(Board &b) override;
};


class Level3: public Computer {
  public:
    Level3(char colour,char pt);
    int cMove(Board &b) override;
};

#endif

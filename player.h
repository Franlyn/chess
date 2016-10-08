#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <vector>
#include "board.h"


class Player {
	char playerType; // either 'H' (human player) or 'C' (computer player)
	char colour; // either 'W' (white) or 'B' (black)
  public:
  	Player(char p, char c);
  	virtual char getPlayerType();
  	virtual char getColourTurn();
  	virtual std::pair<int,char>  moveFrom();
  	virtual std::pair<int,char> moveTo();
	virtual int cMove(Board &b);
  	virtual ~Player();
};


#endif

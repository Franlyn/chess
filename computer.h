#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <iostream>
#include <vector>
#include "player.h"

class Computer: public Player {
	
  public:
  	Computer(char pt, char colour);
  	virtual int cMove(Board &b) override;

};


#endif

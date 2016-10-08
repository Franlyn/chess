#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <iostream>
#include <vector>
#include "player.h"

class Human: public Player {
	
  public:
  	Human(char colour, char pt);
  	void displayInvalid();
  	std::pair<int, char> moveFrom() override;
  	std::pair<int, char> moveTo() override;

};


#endif

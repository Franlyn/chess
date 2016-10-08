#include <iostream>
#include <vector>
#include <utility>
#include "computer.h"

Computer::Computer(char pt, char colour): 
		Player(pt, colour) { }

int Computer::cMove(Board &b) {
	return 1;
}


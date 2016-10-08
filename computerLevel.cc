#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include "board.h"
#include "computerLevel.h"

// Computer: Level 1. Random Legal Moves
Level1::Level1(char colour, char pt): Computer(pt, colour) { }

int Level1::cMove(Board &b) {
	srand (time(NULL));
	
	char colour = getColourTurn();
	int fromSize = b.fromSize(colour, 1);
	if (fromSize == 0) {
		return 1;
	}
	int choose = rand() % fromSize;
	choose = b.toSize(choose, 1);
	choose = rand() % choose;
	b.computerMove(choose, 1);

	return 0;
}


// Computer: Level 2. Prefers capturing moves and checks over other moves.
Level2::Level2(char colour, char pt): Computer(pt, colour) { }

int Level2::cMove(Board &b) {
	srand (time(NULL));

	char colour = getColourTurn();
	int fromSize = b.fromSize(colour, 2);
	if (fromSize == 0) {
		return 1;
	}
	int choose = rand() % fromSize;
	choose = b.toSize(choose, 2);
    choose = rand() % choose;
	b.computerMove(choose, 2);

	return 0;
}



// Computer: Level 3. Prefers avoiding capture, capturing moves, and checks.
Level3::Level3(char colour, char pt): Computer(pt, colour) { }

int Level3::cMove(Board &b) {
	srand (time(NULL));
	char colour = getColourTurn();
	int fromSize = b.fromSize(colour, 3);
	if (fromSize == 0) {
		return 1;
	}
	int choose = rand() % fromSize;
	choose = b.toSize(choose, 3);
	if (choose != -1) {
		return 1;
	} else {
		return 0;
	}
}


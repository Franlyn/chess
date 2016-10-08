#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include "square.h"
#include "window.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "player.h"
class Player;

class Game {
	std::vector<shared_ptr<Player>> players;
	std::vector<double> scores;
	bool resign; // default false
	char firstTurn;
	const int size = 8;
	Board myBoard;
public:
	Game();
	void new_game(Xwindow &w);
	void setUp(Xwindow &w);
	void play(Xwindow &w);
	void humPlay(int np, Xwindow &w);
	void comPlay(int np, Xwindow &w);
	void displayInvalid();
	void displayCheck(char co);
	void displayWon(char co, Xwindow &w, bool isresign);
	void displayCurrentScore();
	void displayFinalScore();
};

#endif

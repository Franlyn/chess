#include <iostream>
#include <string>
#include "window.h"
#include "board.h"
#include "game.h"
using namespace std;

int main () {
	string cmd;
//	int from_r, to_r;
//	char from_c, to_c;
//	Board b;
	Xwindow w;
	Game g;
//	int size = 8;
//	int score = 0;

	while (cin >> cmd) {
		if (cmd == "game") {
			g.new_game(w);
//			g.play();
		} else if (cmd == "setup") {
			g.setUp(w);
			//TODO: modify isWon to Board to modify won
			//if (b.isWon()) { cout << "You win" << endl; }
		}
	}
}

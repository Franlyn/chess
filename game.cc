#include "game.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "player.h"
#include "human.h"
#include "computer.h"
#include "computerLevel.h"
using namespace std;

Game::Game() {
	scores.emplace_back(0.0);
	scores.emplace_back(0.0);
	resign = false;
	firstTurn = 'W';
}

void Game::new_game(Xwindow &w) {
	cin.exceptions(ios::eofbit|ios::failbit);

	// check who move first
	char first = firstTurn;
        char second;
        if (first == 'W') second = 'B';
	else second = 'W'; 

	string p1;
	string p2;
	try {
		cin >> p1;
		cin >> p2;
		if (p1 == "human") {
			this->players.push_back(make_shared<Human>(first, 'H'));
		} else if (p1 == "computer1") {
			this->players.push_back(make_shared<Level1>(first, 'C'));
		} else if (p1 == "computer2") {
			this->players.push_back(make_shared<Level2>(first, 'C'));
		} else if (p1 == "computer3") {
			this->players.push_back(make_shared<Level3>(first, 'C'));
		} else {
			throw;
		}

		if (p2 == "human") {
			this->players.push_back(make_shared<Human>(second, 'H'));
		} else if (p2 == "computer1") {
			this->players.push_back(make_shared<Level1>(second, 'C'));
		} else if (p2 == "computer2") {
			this->players.push_back(make_shared<Level2>(second, 'C'));
		} else if (p2 == "computer3") {
			this->players.push_back(make_shared<Level3>(second, 'C'));
		} else {
			throw;
		}
	}
	catch (...) {
		if (cin.eof()) displayFinalScore();
		else cout << "Invalid input." << endl;
	}
	
	myBoard.init(size, w);
	myBoard.changeSettled(false);
	cout << myBoard;
	play(w);
}


// Set up the board manually
void Game::setUp(Xwindow &w) {
	cin.exceptions(ios::eofbit|ios::failbit);

	// clear myBoard first
	myBoard.createEmpty(size, w);

	string cmd;
	char chess;

	//myBoard.setBoardCoords();

	myBoard.changeSettled(true); // Change settled to true, so init will not init the pieces

	try {
		while (true) {
			cin >> cmd;
			if (cmd == "+") {
				cin >> chess;
				char colour;
				if (chess == 'R' || chess == 'N' || chess == 'B' || chess == 'Q'
				    || chess == 'K' || chess == 'P') {
					colour = 'W';
				} else if (chess == 'r' || chess == 'n' || chess == 'b' || chess == 'q'
					   || chess == 'k' || chess == 'p') {
					colour = 'B';
					chess = chess - 'a' + 'A';
				} else {
					displayInvalid();
                                	continue;
				}

				int take_row;
				char take_col;
				cin >> take_col >> take_row;
				int row = take_row - 1;
				int col = take_col - 'a';
				
				if (row >= 0 && col >= 0 && row <= 7 && col <= 7) { 
					myBoard.addPiece(row, col, chess, colour);
					// redisplay & redraw
					myBoard.init(size, w);
					cout << myBoard;
				} else {
					displayInvalid();
                                	continue;
				}
			
			} else if (cmd == "-") {
				int take_row;
				char take_col;
				cin >> take_col >> take_row;
				int row = take_row - 1;
				int col = take_col - 'a';

				if (row >= 0 && col >= 0 && row <= 7 && col <= 7) { 
					myBoard.removePiece(row, col);
					// redisplay & redraw
					myBoard.init(size, w);
					cout << myBoard;
				} else {
					displayInvalid();
                                	continue;
				}

			} else if (cmd == "=") {
				string colourTurn;
				cin >> colourTurn;
				if (colourTurn == "black") {
					firstTurn = 'B';
				} else if (colourTurn == "white") {
					firstTurn = 'W';
				} else {
					displayInvalid();
                                	continue;
				}

			} else if (cmd == "done") {
				if (!myBoard.checkSetUp()) {
					cout << "Unsatisfied setting. Please give another command" << endl;
					continue;
				} else {
					break;
				}

			} else {
				displayInvalid();
                                continue;
			}
		}
	}

	catch (ios::failure &) {
		if (cin.eof()) displayFinalScore();
	}
}
	


void Game::play(Xwindow &w) {
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	while(!myBoard.isWon()) {
		try {
			// player 1's turn
			if (players[0]->getPlayerType() == 'H') {
				humPlay(1, w);
				// check whether there was a resign
	               		if (this->resign) {
					this->resign = false;
        	        	        displayWon(players[1]->getColourTurn(), w, true);
                		        break;
               			}

			} else {
				comPlay(1, w);
			}

			// player 2's turn
			if (players[1]->getPlayerType() == 'H') {
				humPlay(2, w);
				// check whether there was a resign
	               		if (this->resign) {
					this->resign = false;
        	        	        displayWon(players[0]->getColourTurn(), w, true);
                	      		break;
               			}

			} else {
				comPlay(2, w);
			}
		}
		catch (ios::failure &) {
			if (cin.eof()) {
				displayFinalScore();
				break;
			}
          	        else {
				displayInvalid();
                   	        continue;
                        }
	        }
	}  
}


void Game::humPlay(int np, Xwindow &w) {
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	while (true) {
		// print out whose turn currently is
                if (players[np-1]->getColourTurn() == 'W') cout << "Now is White player's turn:" << endl;
		else cout << "Now is Black player's turn:" << endl;

		cin >> cmd;
		if (cmd == "move") {
			// player 1 makes a move
			if (myBoard.fromSize(players[np-1]->getColourTurn(), 1) == 0) {
				cout << "Draw" << endl;
				scores[0] += 0.5;
				scores[1] += 0.5;
			}
			pair<int, char> from1 = players[np-1]->moveFrom();
			pair<int, char> to1 = players[np-1]->moveTo();

			if (!myBoard.valid(from1.first, from1.second, to1.first, to1.second, players[np-1]->getColourTurn())) {
				cout << "Invalid Move. Please enter another command" << endl;
                                continue;
			}

			// move
			myBoard.move(from1.first, from1.second, to1.first, to1.second);
			
			// display the board
			cout << myBoard;

			// check whether put my opponent in check
			if (np == 1 && myBoard.isCheck(players[1]->getColourTurn())) {
				displayCheck(players[1]->getColourTurn());
			}
			if (np == 2 && myBoard.isCheck(players[0]->getColourTurn())) {
				displayCheck(players[0]->getColourTurn());
			}
               
			// check whether I won
			if (myBoard.isWon(players[np-1]->getColourTurn())) {
				++this->scores[np-1];
				displayWon(players[np-1]->getColourTurn(), w, false);
			}
			break;
		}

		else if (cmd == "resign") {
			if (np == 1) scores[1] += 1;
                        else scores[0] += 1;
			this->resign = true;
			break;
		}
 
		else {
			displayInvalid();
			continue;
		}
	}
}

void Game::comPlay(int np, Xwindow &w) {
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	while (true) {
                try {
                        cin >> cmd;
                        if (cmd != "move") throw;
                        else break;
                }
                catch (ios::failure &) {
                        if (cin.eof()) {
                                displayFinalScore();
                                return;
                        }
                        else {
                                displayInvalid();
                                continue;
                        }
                }
        }
	int succeed = players[np-1]->cMove(myBoard);
	if (succeed == 1) {
		cout << "Draw" << endl;
		scores[0] += 0.5;
		scores[1] += 0.5;
	}
	if (np == 1 && myBoard.isCheck(players[1]->getColourTurn())) {
        	displayCheck(players[1]->getColourTurn());
        }
	cout << myBoard;
        if (np == 2 && myBoard.isCheck(players[0]->getColourTurn())) {
        	displayCheck(players[0]->getColourTurn());
        }
	if (myBoard.isWon(players[np-1]->getColourTurn())) {
		++this->scores[np-1];
		displayWon(players[np-1]->getColourTurn(), w, false);
	}

}

void Game::displayInvalid() {
	cout << "Invalid input. Please give another command." << endl;
}

void Game::displayCheck(char co) {
	if (co == 'W') {
		cout << "White is in check." << endl;
	} else {
		cout << "Black is in check." << endl;
	}
}

void Game::displayWon(char co, Xwindow &w, bool isresign) {
	if (co == 'W') {
		if (isresign) cout << "You resigned! White wins!" << endl;
		else cout << "Checkmate! White wins!" << endl;
	} 
	else {
		if (isresign) cout << "You resigned! Black wins!" << endl;
		else cout << "Checkmate! Black wins!" << endl;
	}
	
	cout << "Do you want to continue? y/n" << endl;
        string answer;
	cin >> answer;
	if (answer == "Y" || answer == "y") {
		cout << "type 'setup' to enter setup mode; otherwise type 'skip' to use the default setup" << endl;
		cin >> answer;
		if (answer == "setup") setUp(w);
               	else {
			myBoard.changeSettled(false);
			myBoard.init(size, w);
		}
		cout << myBoard;
		play(w);
		
	}
	else {
		displayCurrentScore();
	}
}


void Game::displayCurrentScore() {
        cout << "Current Score:" << endl;
        cout << "White: " << scores[0] << endl;
        cout << "Black: " << scores[1] << endl;
}


void Game::displayFinalScore() {
	cout << "Final Score:" << endl;
	cout << "White: " << scores[0] << endl;
	cout << "Black: " << scores[1] << endl;
}


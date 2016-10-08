#include <vector>
#include <iostream>
#include <memory>
#include "board.h"
#include "window.h"
using namespace std;

Board::Board(): size{size}, capture{false}, 
	check{false} { 
	choices.resize(16);
	for (int i = 0; i < 16; ++i){
		choices[i].resize(7);
	}
	attack.resize(16);
        for (int i = 0; i < 16; ++i){
                attack[i].resize(6);
        }
	check1.resize(16);
        for (int i = 0; i < 16; ++i){
                check1[i].resize(6);
        }
	avoidCapture.resize(128);
        for (int i = 0; i < 16; ++i){
                avoidCapture[i].resize(6);
        }
}

Board::~Board() {
	clearBoard();
	td.reset();
	gd.reset();
}

void Board::clearBoard() {
	theBoard.clear();
}

void Board::createEmpty(int s, Xwindow &w) {
	this->size = s;
	clearBoard();
	theBoard.resize(s);
        for (int i = 0; i < s; ++i) {
        	theBoard[i].resize(s);
       	}


	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			theBoard[i][j].setCoords(i, j);
			// attach to all the squares
			for (int a = 0; a < size; ++a) {
				for (int b = 0; b < size; ++b) {
					shared_ptr<Observer> o(shared_ptr<Observer> (), &theBoard[a][b]);
					theBoard[i][j].attach(o);
				}
			}
		}
	}

	td = make_shared<TextDisplay> (size, theBoard);
        gd = make_shared<GraphicsDisplay> (size, theBoard, w);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			theBoard[i][j].attach(td);
		        theBoard[i][j].attach(gd);
			theBoard[i][j].notify(theBoard[i][j], theBoard);
		}
	}
}


int Board::numPossibleMoves(int r, char c) {
	int row = r - 1;
	int col = c - 'a';
	return theBoard[row][col].sizeMove();
}

int Board::numPossibleAttacks(int r, char c) {
	int row = r - 1;
	int col = c - 'a';
	return theBoard[row][col].sizeAttack();
}

int Board::numPossibleChecks(int r, char c) {
	int row = r - 1;
	int col = c- 'a';
	return theBoard[row][col].sizeCheck();
}

void Board::addPiece(int r, int c, char chess, char colour) {
	theBoard[r][c].setPiece(chess, colour, theBoard);
	theBoard[r][c].notifyAll(theBoard);
}

void Board::removePiece(int r, int c) {
	if (!theBoard[r][c].isEmpty()) {
		theBoard[r][c].clearPiece();
		theBoard[r][c].notifyAll(theBoard);
	}
}

bool Board::checkSetUp(){
	for (int j = 0; j < size; ++j) {
		if (theBoard[0][j].getType() == 'P' || theBoard[7][j].getType() == 'P') {
			return false;
		}
	}
	return !isCheck();
}

void Board::changeSettled(bool change) {
	settled = change;
}

void Board::setBoardCoords() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
        		theBoard[i][j].setCoords(i, j);
		}
	}
}


void Board::init(int s, Xwindow &w) {
	this->size = s;
	if (!settled) {
		clearBoard();
		theBoard.resize(s);
        	for (int i = 0; i < s; ++i) {
        		theBoard[i].resize(s);
        	}
	}
	

	char colour = 'B';

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (!settled){
				theBoard[i][j].setCoords(i, j);
				if (i == 6) {
					colour = 'B';
					theBoard[i][j].setPiece('P', colour, theBoard);
				} else if (i == 1) {
					colour = 'W';
					theBoard[i][j].setPiece('P', colour, theBoard);
				} else if (i == 0) {
					colour = 'W';
					if (j == 0 || j == 7) {
						theBoard[i][j].setPiece('R', colour, theBoard);
					} else if (j == 1 || j == 6) {
						theBoard[i][j].setPiece('N', colour, theBoard);
					} else if (j == 2 || j == 5) {
						theBoard[i][j].setPiece('B', colour, theBoard);
					} else if (j == 3) {
						theBoard[i][j].setPiece('Q', colour, theBoard);
					} else if (j == 4) {
						theBoard[i][j].setPiece('K', colour, theBoard);
					}
				} else if (i == 7) {
					colour = 'B';
					if (j == 0 || j == 7) {
						theBoard[i][j].setPiece('R', colour, theBoard);
					} else if (j == 1 || j == 6) {
						theBoard[i][j].setPiece('N', colour, theBoard);
					} else if (j == 2 || j == 5) {
						theBoard[i][j].setPiece('B', colour, theBoard);
					} else if (j == 3) {
						theBoard[i][j].setPiece('Q', colour, theBoard);
					} else if (j == 4) {
						theBoard[i][j].setPiece('K', colour, theBoard);
					}
				}
			}
			

			// attach to all the squares
			for (int a = 0; a < size; ++a) {
				for (int b = 0; b < size; ++b) {
					shared_ptr<Observer> o(shared_ptr<Observer> (), &theBoard[a][b]);
					theBoard[i][j].attach(o);
				}
			}

		}
	}
	td = make_shared<TextDisplay> (size, theBoard);
    gd = make_shared<GraphicsDisplay> (size, theBoard, w);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			theBoard[i][j].attach(td);
		        theBoard[i][j].attach(gd);
			theBoard[i][j].notify(theBoard[i][j], theBoard);
		}
	}
    
	settled = true;
}


bool Board::isWon() { //can set the pos of Kings to be fields in board
	int count = 0;
	for (int i = 0; i <= 7; ++i) {
		for (int j = 0; j <= 7; ++j) {
			if (theBoard[i][j].getType() == 'K') {
				count++;
			}
			if (count == 2) return false;
		}
	}
	return true;
}

bool Board::isWon(char co) {
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (!theBoard[i][j].isEmpty() && (theBoard[i][j].getType() == 'K') &&
			    (theBoard[i][j].getColour() != co)) return false;
		}
	}
	return true;
}



bool Board::isCheck() {
	int whiteKing = 0;
	int blackKing = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (theBoard[i][j].getType() == 'K' && (!theBoard[i][j].inCheck(i, j))) {
				if (theBoard[i][j].getColour() == 'W') {
					whiteKing++;
				} else {
					blackKing++;
				}
			}
		}
	}
	return !(whiteKing == 1 && blackKing == 1);
}

bool Board::isCheck(char co) {
	bool notWon = false;
	bool inCheck = false;
	for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                        if (theBoard[i][j].getType() == 'K' && (theBoard[i][j].getColour() == co) &&
			    (theBoard[i][j].inCheck(i, j))) {
                        	inCheck = true;
                        }
			if (theBoard[i][j].getType() == 'K' && (theBoard[i][j].getColour() != co)) {
				notWon = true;
			}
                }
        }
	return (notWon && inCheck);
}



bool Board::isCapture() { return capture; }



int Board::fromSize(char co, int level) {
    int countM = 0;
    int countA = 0;
    int countC = 0;
    int countAC = 0;
    int n = 0;
    if (level == 0) {	 // Human
        int countH = 0;
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if (theBoard[i][j].getColour() ==  co && !(theBoard[i][j].isEmpty())
                    && (theBoard[i][j].sizeMove() != 0)) {
                    countH++;
                }
            }
        }
        return countH;
    }
    
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if (theBoard[i][j].getColour() ==  co && !(theBoard[i][j].isEmpty())
                && (theBoard[i][j].sizeMove() != 0)) {
                choices[n][0] = i;
                choices[n][1] = j;
                choices[n][2] = theBoard[i][j].sizeMove();
                choices[n][3] = theBoard[i][j].sizeAttack();
                choices[n][4] = theBoard[i][j].sizeCheck();
                
                if (choices[n][3] != 0) {
                    attack[countA][0] = i;
                    attack[countA][1] = j;
                    attack[countA][3] = theBoard[i][j].sizeAttack();
                    countA++;
                }
                if (choices[n][4] != 0) {
                    check1[countC][0] = i;
                    check1[countC][1] = j;
                    check1[countC][3] = theBoard[i][j].sizeCheck();
                    countC++;
                }
                
                n++;
                countM++;
            }
        }
    }
    attack[0][5] = countA;
    check1[0][5] = countC;
    
    if (level == 3) {
        if (countA > 0) {
            for (int s = 0; s < countA; ++s) {
                int r = attack[s][0];
                int c = attack[s][1];
                int sm = theBoard[r][c].sizeAttack();
                for (int num = 0; num < sm; ++num) {
                    int i = theBoard[r][c].getAttackCoord(num).first;
                    int j = theBoard[r][c].getAttackCoord(num).second;
                    avoidCapture[countAC][0] = r;
                    avoidCapture[countAC][1] = c;
                    avoidCapture[countAC][2] = i;
                    avoidCapture[countAC][3] = j;
                    avoidCapture[countAC][4] = s;
                    countAC++;
                    
                }
            }
        }
        if (countAC == 0 && countC > 0) {
            for (int s = 0; s < countC; ++s) {
                int r = check1[s][0];
                int c = check1[s][1];
                int sm = theBoard[r][c].sizeCheck();
                for (int num = 0; num < sm; ++num) {
                    int i = theBoard[r][c].getCheckCoord(num).first;
                    int j = theBoard[r][c].getCheckCoord(num).second;
                    cout << "C: r,c" << r << "," << c << " i, j" << i << "," << j << endl;
                    if (theBoard[r][c].canAvoidCapture(i, j)) {
                        avoidCapture[countAC][0] = r;
                        avoidCapture[countAC][1] = c;
                        avoidCapture[countAC][2] = i;
                        avoidCapture[countAC][3] = j;
                        avoidCapture[countAC][4] = s;
                        countAC++;
                    }
                }
            }
        }
        if (countAC == 0 && countM > 0) {
            for (int s = 0; s < countM; ++s) {
                int r = choices[s][0];
                int c = choices[s][1];
                int sm = theBoard[r][c].sizeMove();
                for (int num = 0; num < sm; ++num) {
                    int i = theBoard[r][c].getMoveCoord(num).first;
                    int j = theBoard[r][c].getMoveCoord(num).second;
                    if (theBoard[r][c].canAvoidCapture(i, j)) {
                        avoidCapture[countAC][0] = r;
                        avoidCapture[countAC][1] = c;
                        avoidCapture[countAC][2] = i;
                        avoidCapture[countAC][3] = j;
                        avoidCapture[countAC][4] = s;
                        countAC++;
                    }
                }
            }
        }
        
        avoidCapture[0][5] = countAC;
        return countAC;
    }else if (level == 2) {
        if (countA + countC != 0) {
            return countA + countC;
        }
    }
    
    return countM;
}

int Board::toSize(int rand, int level) {
    if (level == 3 && rand < avoidCapture[0][5]) {
        int r1 = avoidCapture[rand][0];
        int c1 = avoidCapture[rand][1];
        int r2 = avoidCapture[rand][2];
        int c2 = avoidCapture[rand][3];
        theBoard[r1][c1].move_piece(r2, c2, theBoard);
        return -1;		// No need to call computerMove
    }
    avoidCapture.clear();
    avoidCapture.resize(128);
    for (int i = 0; i < 128; ++i) { avoidCapture[i].resize(6); }
    
    if (level == 2) {
        
        if (rand >= (attack[0][5] + check1[0][5])) {
            choices[0][0] = choices[rand][0];
            choices[0][1] = choices[rand][1];
            choices[0][6] = 0;
        } else if (rand < attack[0][5]) {
            choices[0][0] = attack[rand][0];
            choices[0][1] = attack[rand][1];
            choices[0][6] = 1;
            return attack[rand][3];
        } else {
            rand -= attack[0][5];
            choices[0][0] = check1[rand][0];
            choices[0][1] = check1[rand][1];
            choices[0][6] = 2;
            return check1[rand][3];
        }
    }
    
    return choices[rand][2];
}

void Board::computerMove(int rand, int level) {
    int i = choices[0][0];
    int j = choices[0][1];
    if (level == 1) {
        
        int r = theBoard[i][j].getMoveCoord(rand).first;
        int c = theBoard[i][j].getMoveCoord(rand).second;

        theBoard[i][j].move_piece(r, c, theBoard);
    } else if (level == 2) {
        if (choices[0][6] == 1) {
            int r = theBoard[i][j].getAttackCoord(rand).first;
            int c = theBoard[i][j].getAttackCoord(rand).second;
            theBoard[i][j].move_piece(r, c, theBoard);
        } else if (choices[0][6] == 2) {
            int r = theBoard[i][j].getCheckCoord(rand).first;
            int c = theBoard[i][j].getCheckCoord(rand).second;
            theBoard[i][j].move_piece(r, c, theBoard);
        } else {
            int r = theBoard[i][j].getMoveCoord(rand).first;
            int c = theBoard[i][j].getMoveCoord(rand).second;
            theBoard[i][j].move_piece(r, c, theBoard);
        }
    }
    choices.clear();
    choices.resize(16);
    for (int i = 0; i < 16; ++i) { choices[i].resize(7); }
    attack.clear();
    attack.resize(16);
    for (int i = 0; i < 16; ++i) { attack[i].resize(6); }
    check1.clear();
    check1.resize(16);
    for (int i = 0; i < 16; ++i) { check1[i].resize(6); }
}
void Board::move(int r1, char c1, int r2, char c2) {
	
	int row = r1 - 1;
	int col = c1 - 'a';
	int row2 = r2 - 1;
	int col2 = c2 - 'a';

	if (theBoard[row][col].canAttack(row2, col2)) { capture = true; }
        else { capture = false; }
	theBoard[row][col].move_piece(row2, col2, theBoard);
}

bool Board::valid(int r1, char c1, int r2, char c2, char co) {
	int row = r1 - 1;
	int col = c1 - 'a';
	int row2 = r2 - 1;
	int col2 = c2 - 'a';
	if (theBoard[row][col].isEmpty() || theBoard[row][col].getColour() != co) {
		return false;
	} else {
		return theBoard[row][col].canMove(row2, col2);
	}
}


ostream& operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}

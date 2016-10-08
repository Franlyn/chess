#include <iostream>
#include <vector>
#include <memory>
#include "textdisplay.h"
#include "square.h"
using namespace std;

TextDisplay::TextDisplay(int n, vector<vector <Square>> &theBoard): 
				theDisplay(n, vector<char>(n)), boardSize{n} {
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			if (theBoard[boardSize - 1 -i][j].isEmpty()) {
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
					theDisplay[boardSize - 1 - i][j] = '_';
				} else {
					theDisplay[boardSize - 1 - i][j] = ' ';
				}
			} else {
				if (theBoard[boardSize - 1 -i][j].getColour() == 'B') {
					char type = theBoard[boardSize - 1 -i][j].getType() - 'A' + 'a';
					theDisplay[i][j] = type;
				} else {
					theDisplay[i][j] = theBoard[boardSize - 1 -i][j].getType();
				}	
			}
		}
	}
}

void TextDisplay::notify(Square &s, vector<vector<Square>> &theBoard) {
	int row = boardSize - 1 - s.getRow();
	int col = s.getCol();
	if (s.isEmpty()) {
		if ((s.getRow() % 2 == 0 && s.getCol() % 2 == 0) || (s.getRow() % 2 == 1 && s.getCol() % 2 == 1)) {
			theDisplay[row][col] = '_';
		} else {
			theDisplay[row][col] = ' ';
		}
	} else {
		if (s.getColour() == 'B') {
			theDisplay[row][col] = s.getType() + 'a' - 'A';
		} else {
			theDisplay[row][col] = s.getType();
		}
	}
}

TextDisplay::~TextDisplay() { theDisplay.clear(); }

ostream &operator<<(ostream &out, const TextDisplay &td) {
	int row_num = 8;
	for (unsigned int row = 0; row < td.theDisplay.size(); ++row) {
		cout << row_num << ' ';
		for (unsigned int col = 0; col < td.theDisplay.size(); ++col) {
			out << td.theDisplay[row][col];
		}
		out << endl;
		row_num--;
	}
	out << endl;
	out << "  abcdefgh" << endl;
	return out;
}

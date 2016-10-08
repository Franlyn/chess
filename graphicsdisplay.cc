#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include "graphicsdisplay.h"
#include "window.h"
#include "square.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n, vector<vector <Square>> &theBoard, Xwindow &window):
		w{window}, squareSize{600/(n+1)} {
	//initialize the window
	int boardSize = theBoard.size();
	w.fillRectangle(0, 0, 600, 600, Xwindow::White);
	int theRow = 8;
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			 if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
                                w.fillRectangle((boardSize - i) * squareSize, j * squareSize,
                        squareSize, squareSize, Xwindow::Black);
                        }
		}
	}
	for (int i = 0; i < boardSize; ++i) {
		stringstream ss1;
		string s1;
		ss1 << theRow;
		ss1 >> s1;
		w.drawBigString(20, i * squareSize + 40, s1, 1);
		theRow--;
		for (int j = 0; j < boardSize; ++j) {
			if (!(theBoard[boardSize - 1 -i][j].isEmpty())) {
				char type;
				int color;
				if (theBoard[boardSize - 1 -i][j].getColour() == 'B') {
					type = theBoard[boardSize - 1 -i][j].getType() - 'A' + 'a';
					color = 2;
				} else {
					type = theBoard[boardSize - 1 -i][j].getType();
					color = 4;
				}
				stringstream ss;
				string s;
				ss << type;
				ss >> s;
				int row = theBoard[i][j].getRow();
				int col = theBoard[i][j].getCol();

				w.drawBigString((col+1) * squareSize + 20, row * squareSize + 40, s, color);
			}
		}
	}

	int row = 0;
	for (int i = 1; i <= 8; ++i) {
		char ch_row = 'a' + row;
		stringstream ss2;
		string s2;
		ss2 << ch_row;
		ss2 >> s2;
		w.drawBigString(20 + i * squareSize, 575, s2, 1);
		row++;
	}
}


void GraphicsDisplay::notify(Square &s, vector<vector<Square>> &theBoard) {
	int row = 7 - s.getRow();
	int col = 1 + s.getCol();
	if (!s.isEmpty()) {
		char type;
		int color;
		if (s.getColour() == 'B') {
			color = 2;
			type = s.getType() + 'a' - 'A';
		} else {
			color = 4;
			type = s.getType();
		}
		stringstream ss;
                string str;
                ss << type;
                ss >> str;
		if ((s.getRow() % 2 == 0 && s.getCol() % 2 == 0) || (s.getRow() % 2 == 1 && s.getCol() % 2 == 1)){
                w.fillRectangle(col * squareSize, row * squareSize,
                        squareSize, squareSize, Xwindow::Black);
        	} else {
                w.fillRectangle(col * squareSize, row * squareSize,
                        squareSize, squareSize, Xwindow::White);
		}
		w.drawBigString(col * squareSize + 20, row * squareSize + 40, str, color);
	} else if ((s.getRow() % 2 == 0 && s.getCol() % 2 == 0) || (s.getRow() % 2 == 1 && s.getCol() % 2 == 1)){
			w.fillRectangle(col * squareSize, row * squareSize, 
			squareSize, squareSize, Xwindow::Black);
	} else {
		w.fillRectangle(col * squareSize, row * squareSize,
                        squareSize, squareSize, Xwindow::White);
	}
}

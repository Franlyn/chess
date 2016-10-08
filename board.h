#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include "square.h"
#include "window.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;

class Board {
  private:
    
    vector<vector<Square>> theBoard;
    vector<vector<int>> choices;
    vector<vector<int>> attack;
    vector<vector<int>> check1;
    vector<vector<int>> avoidCapture;
    
    int size;
    bool capture = false;
    bool check = false;
    shared_ptr<TextDisplay> td;
    shared_ptr<GraphicsDisplay> gd;
    bool settled = false;
    void clearBoard();
    
  public:
    Board();
    ~Board();
    void createEmpty(int s, Xwindow &w);

    int numPossibleMoves(int r, char c);
    int numPossibleAttacks(int r, char c);
    int numPossibleChecks(int r, char c);
    
    void addPiece(int r, int c, char chess, char colour);
    void removePiece(int r, int c);
    bool checkSetUp();
    void changeSettled(bool change);
    void setBoardCoords();
	
    void init(int s, Xwindow &w);
    bool isWon();
    bool isWon(char co);
    bool isCheck();
    bool isCheck(char co);
    bool isCapture();

    int fromSize(char co, int level);    // also modify vector choices
    int toSize(int rand, int level);     // take a random number, return the size of To. From:(choices[0][0],choices[0][1])
    void computerMove(int rand, int level); // rand for choosing getMoveCoord and blah


    void move(int r1, char c1, int r2, char c2);
    bool valid(int r1, char c1, int r2, char c2, char co);
    friend ostream& operator<<(ostream &out, const Board &b);

};
#endif

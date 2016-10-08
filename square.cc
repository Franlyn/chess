#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include "square.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "bishop.h"

using namespace std;

Square::Square() { }

Square::~Square() {
	piece.reset();
}


int Square::getRow() {
	return r;
}

int Square::getCol() {
	return c;
}

bool Square::isEmpty() {
	return (piece == nullptr);
}

void Square::setType(char type) {
	chess_type = type;
}

void Square::setColour(char co) {
        colour = co;
}

char Square::getType() {
	return chess_type;
}

char Square::getColour() {
	return colour;
}

void Square::setCoords(int row, int col) {
	this->r = row;
	this->c = col;
}

void Square::setPiece(char type, char co, vector<vector <Square>> &theBoard) {
	chess_type = type;
	colour = co;
	
	if (chess_type == 'P') {
		piece = make_shared<Pawn> (type, co, theBoard, r, c);
	} else if (chess_type == 'N') {
		piece = make_shared<Knight> (type, co, theBoard, r, c);
	} else if (chess_type == 'R') {
		piece = make_shared<Rook> (type, co, theBoard, r, c);
	} else if (chess_type == 'B') {
		piece = make_shared<Bishop> (type, co, theBoard, r, c);
	} else if (chess_type == 'Q') {
		piece = make_shared<Queen> (type, co, theBoard, r, c);
	} else if (chess_type == 'K') {
		piece = make_shared<King> (type, co, theBoard, r, c);
	}

}

void Square::clearPiece() {
	piece.reset();
	colour = 'X';
	chess_type = 'X';
}

bool Square::canMove(int r, int c) {
	if (chess_type == 'K' && inCheck(r, c)) return false;
	return piece->inPossibleMoves(r, c);
}

bool Square::canAttack(int r, int c) { // check if (r, c) is in possibleAttacks
	return piece->inPossibleAttacks(r, c);
}

bool Square::canAvoidCapture(int r, int c) {
        return piece->captureFree(r, c);
}

std::pair<int, int> Square::getMoveCoord(int rand) {
	return piece->getMove(rand);
}

std::pair<int, int> Square::getAttackCoord(int rand) {
        return piece->getAttack(rand);
}

std::pair<int, int> Square::getCheckCoord(int rand) {
        return piece->getCheck(rand);
}

int Square::sizeMove() {
	return piece->sizeMoves();
}

int Square::sizeAttack() {
	return piece->sizeAttacks();
}

int Square::sizeCheck() {
	return piece->sizeChecks();
}

void Square::addMove(int r, int c) {
        piece->addPossibleMove(r, c);
}

void Square::addAttack(int r, int c) {
        piece->addPossibleAttack(r, c);
}

bool Square::inCheck(int r, int c) { // For King
	if (piece && chess_type == 'K') {
		return piece->isInCheck(r, c);
	}
	return false;
}

bool Square::firstMove() {
	if (piece && chess_type == 'R') { // For Rook
		return piece->isFirstMove();
	}
	return false;
}

bool Square::secondMove() {
	if (piece && chess_type == 'P') { // For Pawn
		return piece->isSecondMove();
	}
	return false;
}

void Square::attach(const shared_ptr<Observer>& o) {
	observers.emplace_back(o);
}

void Square::notify(Square &, vector<vector<Square>> &theBoard) {	// Be notified by Square &
	if (piece) {
		piece->update(theBoard);
	}
}

void Square::notifyAll(vector<vector<Square>> &theBoard) { // Notify all observers, including itself
	for (unsigned int i = 0; i < observers.size(); ++i) {
		observers[i]->notify(*this, theBoard);
	}
}

// check if it can move to (r, c), then move
void Square::move_piece(int r, int c, vector<vector <Square>> &theBoard) {
	int row = r;
	int col = c;
 
	if (!canMove(row, col)) {
		cout << "Illegal Move!" << endl;
	} 

	else if ((theBoard[row][col].piece == nullptr) && (chess_type == 'K') && (inCheck(row, col)) ) {
		cout << "Illegal move! Your King will be in check!" << endl;
        }

        else if (theBoard[row][col].piece == nullptr) {

		// castling
		if ((piece->getType() == 'K' || piece->getType() == 'R') && piece->isFirstMove()) {
			piece->setNotFirst();
		}

		if ( (piece->getType() == 'K') && 
			((abs(row - getRow()) == 2) || (abs(col - getCol()) == 2)) ) {
			if ((theBoard[row][col+1].piece) && (theBoard[row][col+1].piece)->getType() == 'R') {
				swap(theBoard[row][col+1].piece, theBoard[row][5].piece);
				theBoard[row][5].piece->setPieceCoords(row, 5);
				swap(theBoard[row][col+1].chess_type, theBoard[row][5].chess_type);
                		swap(theBoard[row][col+1].colour, theBoard[row][5].colour);
				theBoard[row][col+1].notifyAll(theBoard);
				theBoard[row][5].notifyAll(theBoard);
			} 
			else if ((theBoard[row][col-2].piece) && (theBoard[row][col-2].piece)->getType() == 'R') {
				swap(theBoard[row][col-2].piece, theBoard[row][3].piece);
				theBoard[row][3].piece->setPieceCoords(row, 3);
                                swap(theBoard[row][col-2].chess_type, theBoard[row][3].chess_type);
                                swap(theBoard[row][col-2].colour, theBoard[row][3].colour);
				theBoard[row][col-2].notifyAll(theBoard);
                                theBoard[row][3].notifyAll(theBoard);
			}
		}

		// en passant
		if (piece->getType() == 'P' && piece->isFirstMove()) {
                        piece->setNotFirst();
                }
		
		if (piece->getType() == 'P' && (abs(row - getRow()) == 2) &&
		    ((theBoard[row][col+1].piece && theBoard[row][col+1].piece->getType() == 'P'&& 
                      theBoard[row][col+1].piece->getColour() != colour) ||
		     (theBoard[row][col-1].piece && theBoard[row][col-1].piece->getType() == 'P' && 
                      theBoard[row][col-1].piece->getColour() != colour))) { 
		        piece->setSecond();
		}

		if (piece->getType() == 'P' && (abs(row - getRow()) == 1) && (col == getCol()) &&
		    piece->isSecondMove()) { 
			piece->setNotSecond();
		}

		if (piece->getType() == 'P' && ((abs(row - getRow()) == 1) && (abs(col - getCol()) == 1))) {
			if (theBoard[row+1][col].piece && theBoard[row+1][col].piece->getType() == 'P' && 
			    theBoard[row+1][col].piece->getColour() != colour) {
				theBoard[row+1][col].clearPiece();
				theBoard[row+1][col].setColour('X');
				theBoard[row+1][col].setType(' ');
				theBoard[row+1][col].notifyAll(theBoard);
			}
			 else if (theBoard[row-1][col].piece && theBoard[row-1][col].piece->getType() == 'P' && 
			    theBoard[row-1][col].piece->getColour() != colour) {
				theBoard[row-1][col].clearPiece();
				theBoard[row-1][col].setColour('X');
				theBoard[row-1][col].setType(' ');
				theBoard[row-1][col].notifyAll(theBoard);
			}
		}

		swap(chess_type, theBoard[row][col].chess_type);
		swap(colour, theBoard[row][col].colour);
		swap(piece, theBoard[row][col].piece);
		theBoard[row][col].piece->setPieceCoords(row, col);
	        
		theBoard[row][col].notifyAll(theBoard);
		notifyAll(theBoard);
	} 
	else if (theBoard[row][col].piece != nullptr) {
		attack_piece(row, col, theBoard);
	}
}

void Square::attack_piece(int r, int c, vector<vector <Square>> &theBoard) {
	int row = r;
	int col = c;
	if (canAttack(row, col)) { // must be

		if (piece->getType() == 'P' && (abs(row - getRow()) == 1) && (abs(col - getCol()) == 1) &&
                    piece->isSecondMove()) { 
                        piece->setNotSecond(); 
        }
		theBoard[row][col].piece.reset(); // this chess has been eaton
		swap(chess_type, theBoard[row][col].chess_type);
		swap(colour, theBoard[row][col].colour);
		swap(piece, theBoard[row][col].piece);
		theBoard[row][col].piece->setPieceCoords(row, col);
		
		notifyAll(theBoard);
		theBoard[row][col].notifyAll(theBoard);
	}
}

#include <iostream>
#include <vector>
#include "player.h"
using namespace std;


Player::Player(char p, char c): playerType{p}, colour {c} { }

char Player::getColourTurn() {
	return colour;
}

char Player::getPlayerType() {
	return playerType;
}

pair<int,char>  Player::moveFrom() {
	return make_pair(0, 'X');
}

pair<int,char> Player::moveTo() {
	return make_pair(0, 'X');
}

int Player::cMove(Board &b) {
	return 1;
}

Player::~Player() { }

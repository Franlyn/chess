#include <iostream>
#include <vector>
#include <utility>
#include "human.h"
using namespace std;

Human::Human(char colour, char pt): 
		Player(pt, colour) { }

pair<int, char> Human::moveFrom() {
	int r;
	char c;
	while (true) {
		cin >> c >> r;
		if (r < 1 || r > 8 || c < 'a' || c > 'h') {
			displayInvalid();
			continue;
		}
		break;
	}
	return make_pair<int, char> (int(r), char(c));
}

pair<int, char> Human::moveTo() {
	int r;
	char c;
	while (true) {
		cin >> c >> r;
		if (r < 1 || r > 8 || c < 'a' || c > 'h') {
			displayInvalid();
			continue;
		}
		break;
	}
	
	return make_pair<int, char> (int(r), char(c));;
}

void Human::displayInvalid() {
	cout << "Invalid Input. Please re-enter the coordinates" << endl;
}


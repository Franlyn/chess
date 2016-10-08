#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include <memory>
#include "observer.h"

class Square;

class TextDisplay: public Observer {
  private:
	std::vector<std::vector<char>> theDisplay;
  	const int boardSize;
  public:
 	TextDisplay(int n, std::vector<std::vector <Square>> &theBoard);

  	void notify(Square &s, std::vector<std::vector<Square>> &theBoard) override;
  	~TextDisplay();

 	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

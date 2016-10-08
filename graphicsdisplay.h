#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include <memory>
#include <X11/Xlib.h>
#include "window.h"
#include "observer.h"

class Square;

class GraphicsDisplay: public Observer {
  private:
    Xwindow &w;
    const int squareSize;
 public:
    GraphicsDisplay(int n, std::vector<std::vector <Square>> &theBoard, Xwindow &window);

    void notify(Square &s, std::vector<std::vector<Square>> &theBoard) override;

};

#endif

#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <vector>
class Square;

class Observer {
 public:
  virtual void notify(Square &s, std::vector<std::vector<Square>> &theBoard) = 0;
  virtual ~Observer();
};
#endif

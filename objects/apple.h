#ifndef APPLE_HEADER
#define APPLE_HEADER

#include "../view/colors.h"
#include "cell.h"


class Apple {
  Cell appleCell;
public:
  Apple(TextColors_t c, int x, int y): appleCell(x, y, c) {}

  TextColors_t getColor() { return appleCell.getColor(); }

  int getX() const { return appleCell.getX(); }
  int getY() const { return appleCell.getY(); }

  Cell &getCell() { return appleCell; }
};

#endif /* APPLE_HEADER */

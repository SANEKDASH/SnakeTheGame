#ifndef CHANGES_HEADER
#define CHANGES_HEADER

#include "../view/colors.h"

class Cell {
  int x_;
  int y_;

  TextColors_t color_;
public:
  Cell(int x, int y, TextColors_t color) : x_(x), y_(y), color_(color) {}

  int getX() const { return x_; }
  int getY() const { return y_; }

  TextColors_t getColor() const { return color_; }
 
  void setX(int x) { x_ = x; }
  void setY(int y) { y_ = y; }

  void setColor(TextColors_t color) { color_ = color;}
};
#endif /* CHANGES_HEADER */

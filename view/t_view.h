#ifndef TEXT_VIEW_HEADER
#define TEXT_VIEW_HEADER

#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "view.h"
#include "colors.h"
#include "../objects/cell.h"
#include "../model/model.h"

static const char *CLEAR_STR           = "\033[J";
static const char *SET_CURSOR_TO_HOME  = "\033[H";
static const char *HIDE_CURSOR         = "\e[?25l";
static const char *SHOW_CURSOR         = "\e[?25h";

class TextView : public View {
  struct winsize winSize;

  int x_ = 0;
  int y_ = 0;

  Model *model_;
  Control *ctl_;
  
  void setCords(int x, int y);

  void setColor(TextColors_t color_code);

  void clearScreen() { write(STDOUT_FILENO, SET_CURSOR_TO_HOME, strlen(SET_CURSOR_TO_HOME));
             	       write(STDOUT_FILENO, CLEAR_STR,          strlen(CLEAR_STR)); }
  
  void hideCursor()  { write(STDOUT_FILENO, HIDE_CURSOR, strlen(HIDE_CURSOR)); }

  void showCursor()  { write(STDOUT_FILENO, SHOW_CURSOR, strlen(SHOW_CURSOR)); }

  void printObjects();
  
public:
  TextView();

  void run();

  void setModel(Model *model)   { model_ = model; }
  void setControl(Control *ctl) { ctl_   = ctl; };

  int getWinWidth();
  int getWinHeight();

  void printText(TextColors_t color_code, int x, int y, const char *text);
  void printChar(TextColors_t color_code, int x, int y, char c);

  void print(std::list<Snake> &snakes);
  void print(std::list<Apple> &apples);

  void print(Apple &apple);
  void print(Snake &snake);
};

#endif /* TEXT_VIEW_HEADER */

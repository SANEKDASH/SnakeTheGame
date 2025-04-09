#include <cstring>

#include "../model/model.h"
#include "t_view.h"
#include "../objects/snake.h"

TextView::TextView()
{
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winSize);
}

void TextView::setColor(TextColors_t colorCode)
{
  char controlBuf[16];

  sprintf(controlBuf, "\x1B[%dm", colorCode);

  write(STDOUT_FILENO, controlBuf, strlen(controlBuf));
}


void TextView::run()
{
  hideCursor();
  clearScreen();
  
  while (1) {
	char controlChar = ctl_->getControlChar();

	if (controlChar == 'q') {
	  break;
	}

	model_->updateScene(controlChar);

	clearScreen();

	print(model_->getApples());
	print(model_->getBotSnakes());
	print(model_->getPlayerSnakes());

	int snakesCount = model_->getBotSnakes().size() + model_->getPlayerSnakes().size();

	if (snakesCount == 0) {
	  printf("the end...\n");
	  break;
	}
  }
  	
  showCursor();
}

int TextView::getWinWidth()
{
  return winSize.ws_col;
}

int TextView::getWinHeight()
{
  return winSize.ws_row;
}

void TextView::printText(TextColors_t colorCode, int x, int y, const char *text)
{
  int curX = x;
  int curY = y;

  printChar(colorCode, curX, curY, text[0]);

  for (int i = 0; text[i] != '\0'; i++) {
	if (text[i] == '\n') {
	  ++curY;
	  curX = x;
	} else {
	  printChar(colorCode, curX++, curY, text[i]);
	}
  }
}

void TextView::setCords(int x, int y)
{
  x_ = x;
  y_ = y;

  if (x_ > winSize.ws_col || y_ > winSize.ws_row) {
	return;
  }

  char buf[16] = {0};

  sprintf(buf, "\e[%d;%dH", y_, x_);

  write(STDOUT_FILENO, buf, strlen(buf));
}

void TextView::print(Apple &apple)
{
  printChar(apple.getColor(), apple.getX(), apple.getY(), '*');
}

void TextView::print(Snake &snake)
{
  auto snakeParts = snake.getBodyParts();

  auto snakeHead = snake.getHead();

  TextColors_t snakeColor = snake.getColor();

  MoveDirection_t snakeDirection = snake.getDirection();

  char snakeHeadChar = '^';

  switch (snakeDirection) {
  case MOVE_UP: {
	break;
  }
  case MOVE_DOWN: {
	snakeHeadChar = '!';
	break;
  }
  case MOVE_LEFT: {
	snakeHeadChar = '<';
	break;
  }
  case MOVE_RIGHT: {
	snakeHeadChar = '>';
	break;
  }
  default: {
	break;
  }
  }

  printChar(snakeColor, snakeHead.getX(), snakeHead.getY(), snakeHeadChar);

  for (auto &bodyPart : snakeParts) {
	printChar(snakeColor, bodyPart.getX(), bodyPart.getY(), '#');
  }
}

void TextView::print(std::list<Snake> &snakes)
{
  for (auto &snake : snakes) {
	print(snake);
  }
}

void TextView::print(std::list<Apple> &apples)
{
  for (auto &apple : apples) {
	print(apple);
  }
}

void TextView::printChar(TextColors_t colorCode, int x, int y, char c)
{  
  setColor(colorCode);

  setCords(x, y);

  write(STDOUT_FILENO, &c, sizeof(c));
  
  setColor(DEFAULT_COLOR);
}


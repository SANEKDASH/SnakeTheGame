#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#include <functional>
#include <list>
#include <vector>

#include <stdio.h>
#include "cell.h"
#include "../view/colors.h"

constexpr int SNAKE_INIT_LENGTH = 3;

typedef enum {
  MOVE_UP = 0,
  MOVE_DOWN = 1,
  MOVE_LEFT = 2,
  MOVE_RIGHT = 3,
} MoveDirection_t;

static const char DEF_MOVE_UP_CHAR    = 'w';
static const char DEF_MOVE_DOWN_CHAR  = 's';
static const char DEF_MOVE_LEFT_CHAR  = 'a';
static const char DEF_MOVE_RIGHT_CHAR = 'd';

class SnakeBodyPart {
  Cell bodyPartCell;
public:
  SnakeBodyPart(int x, int y, TextColors_t color) : bodyPartCell(x, y, color) {}
  
  TextColors_t getColor() const { return bodyPartCell.getColor(); }

  int getX() const { return bodyPartCell.getX(); }
  int getY() const { return bodyPartCell.getY(); }

  void setX(int x) { bodyPartCell.setX(x); }
  void setY(int y) { bodyPartCell.setY(y); }

  bool operator==(const SnakeBodyPart &other)
  {
	return ((getX() == other.getX()) && (getY() == other.getY()));
  }

  Cell &getCell()
  {
	return bodyPartCell;
  }
};

class Snake {
  std::list<SnakeBodyPart> snakeParts_;

  SnakeBodyPart snakeHead_;
  
  MoveDirection_t moveDirection_ = MOVE_UP;

  TextColors_t color_;

  std::vector<std::pair<char, MoveDirection_t>> ctlChars_;
  
public:
  Snake(TextColors_t color, int x, int y,
		char MOVE_UP_CHAR,   char MOVE_DOWN_CHAR,
		char MOVE_LEFT_CHAR, char MOVE_RIGHT_CHAR): snakeHead_(x, y, color), color_(color)
  {
   	ctlChars_ = {{MOVE_UP_CHAR, MOVE_UP},
				 {MOVE_DOWN_CHAR, MOVE_DOWN},
				 {MOVE_LEFT_CHAR, MOVE_LEFT},
				 {MOVE_RIGHT_CHAR, MOVE_RIGHT}};

	for (int i = 0; i < SNAKE_INIT_LENGTH; ++i) {
	  snakeParts_.push_back({ x, y + 1 + i, color});
	}
  }
  
  int handleOuterCtlChar(char ctlChar)
  {
	for (auto snakeChar : ctlChars_) {
	  if (ctlChar == std::get<0>(snakeChar)) {
		move(std::get<1>(snakeChar));
		return 1;
	  }
	}

	return 0;
  }
  
  void addLen()
  {
	snakeParts_.push_front({snakeHead_.getX(), snakeHead_.getY(), color_});

	MoveDirection_t dir = getDirection();

	switch (dir) {
	case MOVE_UP:
	  if (dir == MOVE_DOWN) {
		snakeHead_.setY(snakeHead_.getY() + 1);	   
		break;
	  }
	  
	  snakeHead_.setY(snakeHead_.getY() - 1);
	  break;

	case MOVE_DOWN:
	  if (dir == MOVE_UP) {
		snakeHead_.setY(snakeHead_.getY() - 1);	  
		break;
	  }
	  
	  snakeHead_.setY(snakeHead_.getY() + 1);
	  break;
	  
	case MOVE_LEFT:
	  if (dir == MOVE_RIGHT) {
		snakeHead_.setX(snakeHead_.getX() + 1);	  
		break;
	  }
	  
	  snakeHead_.setX(snakeHead_.getX() - 1);
	  break;
	  
	case MOVE_RIGHT:
	  if (dir == MOVE_RIGHT) {
		snakeHead_.setX(snakeHead_.getX() + 1);	  
		break;
	  }

	  snakeHead_.setX(snakeHead_.getX() + 1);
	  break;

	default: break;
	}
  }

  std::list<SnakeBodyPart> &getBodyParts() { return snakeParts_; }

  SnakeBodyPart &getHead() {return snakeHead_; }

  TextColors_t getColor() const { return color_; }

  MoveDirection_t getDirection() const { return moveDirection_; }

  void setDirection(MoveDirection_t direction) { moveDirection_ = direction; }

  void move(MoveDirection_t dir)
  {
	MoveDirection_t curDirection = moveDirection_;

	int prevHeadX = snakeHead_.getX();
	int prevHeadY = snakeHead_.getY();
	
	switch (dir) {
	case MOVE_UP:
	  if (curDirection == MOVE_DOWN) {
		dir = MOVE_DOWN;
		snakeHead_.setY(snakeHead_.getY() + 1);	   
		break;
	  }
	  
	  snakeHead_.setY(snakeHead_.getY() - 1);
	  break;

	case MOVE_DOWN:
	  if (curDirection == MOVE_UP) {
		dir = MOVE_UP;
		snakeHead_.setY(snakeHead_.getY() - 1);	  
		break;
	  }
	  
	  snakeHead_.setY(snakeHead_.getY() + 1);
	  break;
	  
	case MOVE_LEFT:
	  if (curDirection == MOVE_RIGHT) {
		dir = MOVE_RIGHT;
		snakeHead_.setX(snakeHead_.getX() + 1);	  
		break;
	  }
	  
	  snakeHead_.setX(snakeHead_.getX() - 1);
	  break;
	  
	case MOVE_RIGHT:
	  if (curDirection == MOVE_LEFT) {
		dir = MOVE_LEFT;
		snakeHead_.setX(snakeHead_.getX() - 1);	  
		break;
	  }

	  snakeHead_.setX(snakeHead_.getX() + 1);
	  break;

	default: break;
	}
 
	moveDirection_ = dir;

	snakeParts_.pop_back();
	snakeParts_.push_front({prevHeadX, prevHeadY, color_});
  }
};
#endif /* SNAKE_HEADER */





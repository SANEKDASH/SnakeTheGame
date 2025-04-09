#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <stdlib.h>
#include <list>
#include <utility>
#include <optional>
#include <utility>


#include "../objects/apple.h"
#include "../objects/snake.h"
#include "../objects/cell.h"

class Model {
  std::list<Apple> apples_;

  std::list<Snake> botSnakes_;
  
  std::list<Snake> playerSnakes_;
  
  int xWinSize_;
  int yWinSize_;

  std::optional<std::pair<int, int>> getCloseApple(Snake &botSnake);  

  void moveBotSnake(Snake &botSnake);

  void eatApples(Snake &snake);

  void placeSnakesInWindow(std::list<Snake> &snakes);

  int checkCollisions(const std::list<Snake>::iterator snake1, std::list<Snake> &snakes);
  
public:
  void initScene(int botCount, const char *player2Ctl);

  void updateScene(char controlChar);

  Apple &addApple(TextColors_t color, int x, int y)
  {
	apples_.push_back({color, x, y});
	return apples_.back();
  };

  Snake &addBotSnake(TextColors_t color, int x, int y)
  {
	botSnakes_.push_back({color, x, y, DEF_MOVE_UP_CHAR,   DEF_MOVE_DOWN_CHAR,
		                               DEF_MOVE_LEFT_CHAR, DEF_MOVE_RIGHT_CHAR});
	return botSnakes_.back();
  };

  Snake &addPlayerSnake(TextColors_t color, int x, int y,
						char moveUpChar,   char moveDownChar,
						char moveLeftChar, char moveRightChar)
  {
	playerSnakes_.push_back({color, x, y, moveUpChar,   moveDownChar,
		                                  moveLeftChar, moveRightChar});
	return botSnakes_.back();
  };
  
  std::pair<int, int> getFreeCords();
  
  int IsCollision(int xCord, int yCord, Snake &snake);
  int IsCollision(int xCord, int yCord, Apple &apple);
  int IsCollision(Snake &snake, Apple &apple);
  int IsCollision(SnakeBodyPart &bodyPart, int xCord, int yCord);

  std::list<Apple> &getApples() { return apples_; };
  
  std::list<Snake> &getPlayerSnakes() { return playerSnakes_; };
  std::list<Snake> &getBotSnakes()    { return botSnakes_; }
  
  void setXWinSize(int xWinSize) { xWinSize_ = xWinSize; };
  void setYWinSize(int yWinSize) { yWinSize_ = yWinSize; };

  int IsInWindow(SnakeBodyPart &snakePart);
  
  void PutObjToWindow(SnakeBodyPart &bodyPart);
};

#endif /* TEXT_VIEW_HEADER */

#include "../view/t_view.h"
#include "model.h"

static const int DEFAULT_BOTS_COUNT = 4;

static int calculateDistance(Apple &apple, Snake &snake);

int Model::IsInWindow(SnakeBodyPart &snakePart)
{
  if (snakePart.getX() > xWinSize_ || snakePart.getY() > yWinSize_) {
	return 0;
  }

  if (snakePart.getX() < 0 || snakePart.getY() < 0) {
	return 0;
  }	

  return 1;
}

void Model::PutObjToWindow(SnakeBodyPart &bodyPart)
{
  if (bodyPart.getX() >= xWinSize_) {
	bodyPart.setX(bodyPart.getX() % xWinSize_);
  }

  if (bodyPart.getX() < 0) {
	bodyPart.setX(xWinSize_ - ((-1) * bodyPart.getX() % xWinSize_));
  }

  if (bodyPart.getY() >= yWinSize_) {
	bodyPart.setY(bodyPart.getY() % yWinSize_);
  }

  if (bodyPart.getY() < 0) {
	bodyPart.setY(yWinSize_ - ((-1) * bodyPart.getY() % yWinSize_));
  }
}

void Model::initScene()
{
  auto freeCords = getFreeCords();  

  addApple(GREEN_COLOR,
  		   std::get<0>(freeCords),
		   std::get<1>(freeCords));

  for (int i = 0; i < DEFAULT_BOTS_COUNT; i++) { 
	freeCords = getFreeCords();

	addBotSnake(WHITE_COLOR, std::get<0>(freeCords),
				std::get<1>(freeCords));
  }  
}

std::pair<int, int> Model::getFreeCords()
{
  int xCord = random() % xWinSize_;
  int yCord = random() % yWinSize_;

  while (1) {
	int collisionCounter = 0;

	for (auto &snake : botSnakes_) {
	  collisionCounter += IsCollision(xCord, yCord, snake);
	}

	for (auto &snake : playerSnakes_) {
	  collisionCounter += IsCollision(xCord, yCord, snake);
	}

	for (auto &apple : apples_) {
	  collisionCounter += IsCollision(xCord, yCord, apple);
	}
	
	if (collisionCounter == 0) {
	  break;
	}

	xCord = random() % xWinSize_;
    yCord = random() % yWinSize_;	
  }
  
  return {xCord, yCord};
}

int Model::IsCollision(int xCord, int yCord, Apple &apple)
{
  if (xCord == apple.getX() && yCord == apple.getY()) {
	return 1;
  }
  
  return 0;
}

int Model::IsCollision(int xCord, int yCord, Snake &snake)
{
  const auto &snakeHead = snake.getHead();
	  
  if (xCord == snakeHead.getX() && yCord == snakeHead.getY()) {
	return 1;
  }

  const auto &snakeParts = snake.getBodyParts();
	  
  for (const auto &snakePart : snakeParts) {
	if (xCord == snakePart.getX() && yCord == snakePart.getY()) {
	  return 1;
	}
  }
	
  return 0;
}

int Model::IsCollision(SnakeBodyPart &bodyPart, int xCord, int yCord)
{
  if (bodyPart.getX() == xCord && bodyPart.getY() == yCord) {
	return 1;
  }
  
  return 0;
}

static int calculateDistance(Apple &apple, Snake &snake)
{
  int snakeHeadX = snake.getHead().getX();
  int snakeHeadY = snake.getHead().getY();

  int appleX = apple.getX();
  int appleY = apple.getY();
  
  return (snakeHeadX - appleX) * (snakeHeadX - appleX) +
	     (snakeHeadY - appleY) * (snakeHeadY - appleY);
}

std::optional<std::pair<int, int>>  Model::getCloseApple(Snake &botSnake)
{
  if (apples_.empty()) {
	return std::nullopt;
  }
  
  auto &closeApple = apples_.front();

  int closeAppleX = closeApple.getX();
  int closeAppleY = closeApple.getY();
  
  int minDistance = calculateDistance(closeApple, botSnake);
  
  for (auto &apple : apples_) {
	int distance = calculateDistance(apple, botSnake);

	if (distance < minDistance) {
	  minDistance = distance;
	  closeAppleX = apple.getX();
	  closeAppleY = apple.getY();
	}
  }

  return std::make_pair(closeAppleX - botSnake.getHead().getX(),
						closeAppleY - botSnake.getHead().getY());
}

void Model::moveBotSnake(Snake &botSnake)
{ 
  if (apples_.empty()) {
	return;
  }
  auto closeAppleCords = getCloseApple(botSnake);

  if (!closeAppleCords.has_value()) {
	return;
  }
  
  int closeAppleX = std::get<0>(closeAppleCords.value());
  if (closeAppleX) {
	if (closeAppleX < 0) {
	  botSnake.move(MOVE_LEFT);
	} else {
	  botSnake.move(MOVE_RIGHT);
	}
	return;
  }

  int closeAppleY = std::get<1>(closeAppleCords.value());
  if (closeAppleY != 0) {
  if (closeAppleY < 0) {
	  botSnake.move(MOVE_UP);
	} else {
	  botSnake.move(MOVE_DOWN);
	}
}
  return;
}

int Model::IsCollision(SnakeBodyPart &part1, SnakeBodyPart &part2)
{
  return ((part1.getX() == part2.getX()) && (part1.getY() == part2.getY()));
}

int Model::IsCollision(Snake &snake, Apple &apple)
{
  const auto &snakeHead = snake.getHead();

  return snakeHead.getX() == apple.getX() && snakeHead.getY() == apple.getY();
}

void Model::eatApples(Snake &snake)
{
  for (auto apple = apples_.begin(); apple != apples_.end();) {
	if (IsCollision(snake, *apple)) {
	  apple = apples_.erase(apple);
	  snake.addLen();	
	} else {
	  apple++;
	} 
  }
}

void Model::placeSnakesInWindow(std::list<Snake> &snakes)
{
  for (auto &snake : snakes) {
	if (!IsInWindow(snake.getHead())) {
	  PutObjToWindow(snake.getHead());
	}

	for (auto &snakeBodyPart : snake.getBodyParts()) {
	  if (!IsInWindow(snakeBodyPart)) {
		PutObjToWindow(snakeBodyPart);
	  }
	}
  }  
}

int Model::checkCollisions(Snake &snake1, std::list<Snake> &snakes)
{
  for (auto &snake2 : snakes) {
	if (&snake1 != &snake2) {
	  if (IsCollision(snake1.getHead(), snake2.getHead())) {
		return 1;
	  }
	}

	for (auto &snake2Part : snake2.getBodyParts()) {
	  if (IsCollision(snake1.getHead(), snake2Part)) {
		return 1;
	  }
	}
  }
  return 0;
}

void Model::update(char controlChar)
{ 
  for (auto &snake : playerSnakes_) {
	if (snake.handleOuterCtlChar(controlChar) == 0) { 
	  snake.move(snake.getDirection());
	}
  }

  for (auto snake = playerSnakes_.begin(); snake != playerSnakes_.end();) {
	int collisionCounter = checkCollisions(*snake, playerSnakes_);
	collisionCounter += checkCollisions(*snake, botSnakes_);

	if (collisionCounter != 0) {
	  snake = playerSnakes_.erase(snake);
	} else {
	  snake++;
	}
  }
  
  for (auto snake = botSnakes_.begin(); snake != botSnakes_.end();) {
	int collisionCounter = checkCollisions(*snake, playerSnakes_);
	collisionCounter += checkCollisions(*snake, botSnakes_);

	if (collisionCounter != 0) {
	  snake = playerSnakes_.erase(snake);
	} else {
	  snake++;
	}
  }

  int snakesCount = botSnakes_.size() + playerSnakes_.size(); 
  
  for (auto &snake :botSnakes_) {
	moveBotSnake(snake);
  }
  
  for (auto &snake : botSnakes_) {
	eatApples(snake);
  }
  for (auto &snake : playerSnakes_) {
	eatApples(snake);
  }

  if (snakesCount == 0) {
	return;
  }
  
  for (; apples_.size() < (snakesCount == 1 ? 1 : snakesCount - 1); ) {
	auto freeCords = getFreeCords(); 
	addApple(GREEN_COLOR, std::get<0>(freeCords), std::get<1>(freeCords));
  }  
  
  placeSnakesInWindow(botSnakes_);
  placeSnakesInWindow(playerSnakes_);
}

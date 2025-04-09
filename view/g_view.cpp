#include "g_view.h"

GraphicView::GraphicView() : width_(DEFAULT_WIDTH),
   	                         height_(DEFAULT_HEIGHT),
	                         wn_(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), std::string(WINDOW_NAME))							 
{  
  if (!appleTxt_.loadFromFile("textures/apple.png")) {
	// do something like throw exception.
  }  

  if (!snakeHeadTxt_.loadFromFile("textures/commander.png")) {
	// do something like throw exception.	
  }

  if (!snakeBodyTxt_.loadFromFile("textures/soldier.png")) {
	// do something like throw exception.	
  }  
}


sf::Color GraphicView::textColorToGraphic(TextColors_t tColor)
{
  switch (tColor) {
  case DEFAULT_COLOR:
  case WHITE_COLOR:   return sf::Color::White;
	
  case RED_COLOR:     return sf::Color::Red;
  case GREEN_COLOR:   return sf::Color::Green;
  case YELLOW_COLOR:  return sf::Color::Yellow;
  case BLUE_COLOR:    return sf::Color::Blue;
  case MAGENTA_COLOR: return sf::Color::Magenta;
  case CYAN_COLOR:    return sf::Color::Cyan;   
  default:            return sf::Color::Transparent;
  }

  return sf::Color::Transparent;
}

void GraphicView::print(Cell &cell)
{
  sf::RectangleShape cellShape(sf::Vector2f(CELL_DEFAULT_SIZE, CELL_DEFAULT_SIZE));

  cellShape.setPosition((int) (cell.getX() * CELL_DEFAULT_SIZE), (int) (cell.getY() * CELL_DEFAULT_SIZE));
  cellShape.setFillColor(textColorToGraphic(cell.getColor()));
  
  wn_.draw(cellShape);
}

void GraphicView::print(Cell &cell, const sf::Texture &txt, float scale)
{
  sf::Sprite cellSprite(txt);
  
  cellSprite.setPosition((int) (cell.getX() * CELL_DEFAULT_SIZE), (int) (cell.getY() * CELL_DEFAULT_SIZE));

  cellSprite.setScale(scale, scale);
  cellSprite.setColor(textColorToGraphic(cell.getColor()));
    
  wn_.draw(cellSprite);
}

void GraphicView::print(Cell &cell, sf::Sprite &sprite, float scale)
{
  sprite.setPosition((int) (cell.getX() * CELL_DEFAULT_SIZE), (int) (cell.getY() * CELL_DEFAULT_SIZE));

  sprite.setScale(scale, scale);
  sprite.setColor(textColorToGraphic(cell.getColor()));

  wn_.draw(sprite);
}

void GraphicView::print(Snake &snake, int frameNumber)
{
  sf::Sprite headSprite(snakeHeadTxt_);
  sf::Sprite bodySprite(snakeBodyTxt_);

  headSprite.setTextureRect(sf::IntRect(frameNumber * SNAKE_SPRITE_SIZE, 0, SNAKE_SPRITE_SIZE, SNAKE_SPRITE_SIZE));
  bodySprite.setTextureRect(sf::IntRect(frameNumber * SNAKE_SPRITE_SIZE, 0, SNAKE_SPRITE_SIZE, SNAKE_SPRITE_SIZE));

  print(snake.getHead().getCell(), headSprite,  CELL_DEFAULT_SIZE / (float) SNAKE_SPRITE_SIZE);

  for (auto &snakePart : snake.getBodyParts()) {
	print(snakePart.getCell(), bodySprite, 0.33);
  }
}

void GraphicView::print(Apple &apple)
{
  print(apple.getCell(), appleTxt_, CELL_DEFAULT_SIZE / (float) APPLE_SPRITE_SIZE);
}

void GraphicView::run()
{
  sf::Clock clock;
  
  while (wn_.isOpen()) {
	wn_.clear();
	
	sf::Event event;

	char ctlChar = EOF;
	
	while(wn_.pollEvent(event)) {
	  if (event.type == sf::Event::Closed) {
	    wn_.close();
	  }

	  if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode < CHAR_MAX) {
		  ctlChar = (char) (event.text.unicode);
		}
	  }
	}	

	model_->updateScene(ctlChar);

	for (auto &apple : model_->getApples()) {
	  print(apple);
	}
	
	for (int i = 0; i < FRAME_COUNT; i++) {
	  for (auto &snake : model_->getBotSnakes()) {
		print(snake, i);
	  }

	  for (auto &snake : model_->getPlayerSnakes()) {
		print(snake, i);
	  }
	  
	  wn_.display();

	  sf::sleep(sf::milliseconds(FRAME_DURATION));
	}
	
    float timeDelta = clock.restart().asSeconds();
	if (TIMEOUT_DURATION - timeDelta > 0) {
	  sf::sleep(sf::milliseconds(TIMEOUT_DURATION - timeDelta));
	}
	
	wn_.display();
	
	ctlChar = EOF;

	if (model_->getBotSnakes().size() + model_->getPlayerSnakes().size() == 0) {
	  wn_.close();
	  break;
	}
  }
}

#ifndef GRAPHIC_VIEW_HEADER
#define GRAPHIC_VIEW_HEADER

#include <climits>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "view.h"
#include "../objects/cell.h"
#include "../objects/apple.h"
#include "../objects/snake.h"

#include "../model/model.h"

#include "colors.h"

static const float TIMEOUT_DURATION = 100; // milliseconds
static const float FRAME_DURATION   = 30;  // milliseconds

static const int DEFAULT_WIDTH  = 800; // pixels
static const int DEFAULT_HEIGHT = 600; // pixels

static const float CELL_DEFAULT_SIZE = 15.f; // pixels

static const int SNAKE_SPRITE_SIZE = 48;  // pixels
static const int APPLE_SPRITE_SIZE = 355; // pixels

static const char *WINDOW_NAME = "Snake the game";

static const int FRAME_COUNT = 3;

class GraphicView : public View {
  int width_;
  int height_;

  sf::RenderWindow wn_;

  sf::Texture appleTxt_;
  sf::Texture snakeHeadTxt_;
  sf::Texture snakeBodyTxt_;
  sf::Texture snakeBodyAngleTxt_;

  Model *model_;
  
  void print(Cell &cell);
  void print(Cell &cell, const sf::Texture &txt, float scale);
  void print(Cell &cell, sf::Sprite &sprite, float scale);
  
  sf::Color textColorToGraphic(TextColors_t tColor);
 public:
  GraphicView();

  void run();

  int getWinWidth()  {  return (int) (((float) width_)  / CELL_DEFAULT_SIZE); }
  int getWinHeight() {  return (int) (((float) height_) / CELL_DEFAULT_SIZE) - 1; }

  void print(Snake &snake, int frameNumber);
  void print(Apple &apple);

  void setModel(Model *model) {model_ = model; }
  
  ~GraphicView() {}
};

#endif

#include "menu.h"

namespace Menu {
    void loop()
  {
    input();
    update();
    draw();
  }
  
  void input()
  {
    if (arduboy.justPressed(A_BUTTON)) {
      Game::init();
      gameState = STATE_GAME;

    }
  }
  
  void update()
  {
    // arduboy.setCursor(16, 16);
  }
  
  void draw()
  {
    // arduboy.print("menu");
  }
}
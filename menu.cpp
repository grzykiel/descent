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
    sprites.drawSelfMasked(112, 1, Fonts::titleFont, 0);
    sprites.drawSelfMasked(109, 10, Fonts::titleFont, 1);
    sprites.drawSelfMasked(107, 19, Fonts::titleFont, 2);
    sprites.drawSelfMasked(106, 28, Fonts::titleFont, 3);
    sprites.drawSelfMasked(107, 37, Fonts::titleFont, 1);
    sprites.drawSelfMasked(109, 46, Fonts::titleFont, 4);
    sprites.drawSelfMasked(112, 54, Fonts::titleFont, 5);
  }
}
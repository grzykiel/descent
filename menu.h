#ifndef MENU_H
#define MENU_H
#include "globals.h"
#include "player.h"
#include "levels.h"
#endif

namespace Menu
{
  void loop();
  void input();
  void update();
  void draw();

  
  void loop()
  {
    input();
    update();
    draw();
  }
  
  void input()
  {
    if (arduboy.justPressed(A_BUTTON)) {
      Player::init();
      Enemies::init();
      Level::init();
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

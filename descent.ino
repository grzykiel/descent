#include "globals.h"
#include "menu.h"
#include "game.h"
#include "player.h"

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  if (!arduboy.nextFrame())
  {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();
  stateLoop();
  arduboy.display();
}

void stateLoop()
{
  switch (gameState)
  {
    case STATE_MENU:
      Menu::loop();
      break;
    case STATE_GAME:
      Game::loop();
      break;
  }
}

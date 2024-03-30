#include <Arduboy2.h>

#include "globals.h"
#include "bitmaps.h"
#include "controls.h"
#include "menu.h"
#include "game.h"
#include "sandbox.h"
#include "player.h"


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FPS);

  switch (gameState) {
    case STATE_GAME:
      Player::init();
      Level::init();
      break;
    case STATE_SANDBOX:
      Sandbox::init();
  }
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();
  stateLoop();
  arduboy.display();
}

void stateLoop() {
  switch (gameState) {
    case STATE_MENU:
      Menu::loop();
      break;
    case STATE_GAME:
      Game::loop();
      break;
    case STATE_SANDBOX:
      Sandbox::loop();
      break;
  }
}

#include <Arduboy2.h>
#include <math.h>

#include "globals.h"
#include "menu.h"
#include "game.h"

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FPS);
  arduboy.initRandomSeed();
  sound.volumeMode(VOLUME_ALWAYS_HIGH);

  switch (gameState) {
    case STATE_GAME:
      Game::init();
      break;
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
  if (gameState == STATE_MENU || gameState == STATE_GAMEOVER || gameState == STATE_PAUSED) {
    Menu::loop();
  } else if (gameState == STATE_GAME || gameState == STATE_DEATH) {
    Game::loop();
  } 
}

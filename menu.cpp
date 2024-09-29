#include "menu.h"

namespace Menu {
const uint8_t textX[] PROGMEM = { 97, 94, 92, 91, 92, 94, 97 };
const uint8_t textFrames[] PROGMEM = { 0, 1, 2, 3, 1, 4, 5 };
const uint8_t blocksX[] PROGMEM = { 47, 47, 50, 50, 53, 59, 59, 59, 59, 65 };
const uint8_t blocksY[] PROGMEM = { 21, 33, 21, 33, 27, 21, 30, 36, 39, 27 };
const uint8_t blocksWidth[] PROGMEM = { 3, 3, 3, 3, 6, 3, 6, 6, 3, 3 };
const uint8_t blocksHeight[] PROGMEM{ 3, 3, 6, 6, 12, 6, 3, 3, 6, 9 };

void loop() {
  input();
  update();
  draw();
}

void input() {
  if (arduboy.justPressed(A_BUTTON)) {
    Game::init();
    gameState = STATE_GAME;
  }
}

void update() {
  // arduboy.setCursor(16, 16);
}

void draw() {
  for (uint8_t i = 0; i < 7; i++) {
    sprites.drawSelfMasked((uint8_t)pgm_read_word(&textX[i]), 1 + i * 9, Fonts::titleFont, (uint8_t)pgm_read_word(&textFrames[i]));
  }

  for (uint8_t i = 0; i < 10; i++) {
    arduboy.fillRect((uint8_t)pgm_read_word(&blocksX[i]), (uint8_t)pgm_read_word(&blocksY[i]), (uint8_t)pgm_read_word(&blocksWidth[i]), (uint8_t)pgm_read_word(&blocksHeight[i]));
  }
}
}
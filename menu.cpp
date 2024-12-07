#include "menu.h"

namespace Menu {
const uint8_t titleX[] PROGMEM = { 97, 94, 92, 91, 92, 94, 97 };
const uint8_t titleFrames[] PROGMEM = { 0, 1, 2, 3, 1, 4, 5 };
const uint8_t blocksX[] PROGMEM = { 47, 47, 50, 59, 59, 59, 62, 65 };
const uint8_t blocksY[] PROGMEM = { 24, 33, 27, 21, 30, 36, 42, 27 };
const uint8_t blocksWidth[] PROGMEM = { 6, 3, 9, 3, 6, 6, 3, 3 };
const uint8_t blocksHeight[] PROGMEM = { 3, 3, 12, 3, 3, 3, 3, 9 };

const uint8_t startText[] PROGMEM = {10, 36, 28, 29, 10, 27, 29};
const uint8_t soundText[] PROGMEM = {11, 36, 28, 24, 30, 23, 13};

uint16_t displayScore = 0;

void loop() {
  if (gameState == STATE_GAMEOVER) {
    gameOver();
    return;
  }
  input();
  draw();
}

void input() {
  if (arduboy.justPressed(A_BUTTON)) {
    Game::init();
    gameState = STATE_GAME;
  } else if (arduboy.justPressed(B_BUTTON)) {
    arduboy.audio.toggle();
    if (arduboy.audio.enabled()) sound.tone(880, 128);
  }
}

void draw() {
  for (uint8_t i = 0; i < 7; i++) {
    sprites.drawSelfMasked((uint8_t)pgm_read_word(&titleX[i]), 1 + i * 9, Fonts::titleFont, (
                            uint8_t)pgm_read_word(&titleFrames[i]));
  }

  for (uint8_t i = 0; i < 8; i++) {
    arduboy.fillRect((uint8_t)pgm_read_word(&blocksX[i]), (uint8_t)pgm_read_word(&blocksY[i]), 
                    (uint8_t)pgm_read_word(&blocksWidth[i]), (uint8_t)pgm_read_word(&blocksHeight[i]));
  }

  Utils::printText(8, 10, startText, 7);
  Utils::printText(1, 10, soundText, 7);
  if (arduboy.audio.enabled()) {
    sprites.drawSelfMasked(1, 46, Fonts::font_5x4, 10);
  }
}

void gameOver() {
  Sprites::drawSelfMasked(72, 18, Fonts::GameOver, 0);
  Sprites::drawSelfMasked(65, 18, Fonts::GameOver, 1);
  Utils::printNum(59, 19, displayScore, 7);
  if (displayScore < score) {
    displayScore+=10;
    sound.tone(880, 10);
  }

  if (arduboy.justPressed(A_BUTTON)) {
    Game::init();
    gameState = STATE_GAME;
    displayScore = 0;
  }

}
}
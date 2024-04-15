#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_GAME;

int16_t cameraOffset = 0;

namespace Utils {

int trim(int p, int l, int h) {
  return min(h, max(p, l));
}

window_t getCollisionWindow(uint16_t x, uint8_t y) {
  window_t wd;
  //TODO use trim()
  wd.yMin = max(floor(y / BLOCKSIZE) - 1, 0);
  wd.yMax = min(ceil(y / BLOCKSIZE) + 1, MAPWIDTH - 1);

  wd.xMin = ceil(x / (1.0f * BLOCKSIZE)) + 1;
  wd.xMax = floor(x / (1.0f * BLOCKSIZE)) - 1;
  wd.xMin = max(MAPHEIGHT - 1 - wd.xMin, 0);
  wd.xMax = min(MAPHEIGHT - 1 - wd.xMax, MAPHEIGHT - 1);

  return wd;
}

}
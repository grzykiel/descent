#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_GAME;

int16_t cameraOffset = 0;

namespace Util {

  int trim(int p, int l, int h) {
    return min(h, max(p, l));
  }

}
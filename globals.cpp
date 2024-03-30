#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_SANDBOX; //STATE_GAME;



namespace Util {

  int trim(int p, int l, int h) {
    return min(h, max(p, l));
  }

}
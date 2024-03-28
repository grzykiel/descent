#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_GAME;

const uint8_t walkSpeed = 1;
const uint8_t walkAnimDelay = 6;
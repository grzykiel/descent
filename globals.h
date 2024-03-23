#include <Arduboy2.h>

#define FPS 60

#define STATE_MENU  0
#define STATE_GAME  1

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_GAME;

const uint8_t walkSpeed = 1;

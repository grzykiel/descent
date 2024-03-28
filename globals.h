#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>

#define FPS 60

#define STATE_MENU  0
#define STATE_GAME  1

#define SCREENLEFT    0
#define SCREENRIGHT   64
#define SCREENTOP     128
#define SCREENBOTTOM  0

//screen dimensions in blocks
#define SCREENWIDTH   8
#define SCREENHEIGHT  16


#define BLOCKSIZE 8
#define PLAYER_WIDTH  8
#define PLAYER_HEIGHT 8

Arduboy2 arduboy;
Sprites sprites;

uint8_t gameState = STATE_GAME;

const uint8_t walkSpeed = 1;
const uint8_t walkAnimDelay = 6;

#endif

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

extern Arduboy2 arduboy;
extern Sprites sprites;

extern uint8_t gameState;

extern const uint8_t walkSpeed;
extern const uint8_t walkAnimDelay;

typedef struct 
{
  uint8_t x;
  uint8_t y;
} vector;

enum class Direction : uint8_t
{
  up,
  down,
  left,
  right
};


namespace Util 
{

}

#endif

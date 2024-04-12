#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>

#define FPS 60

#define STATE_MENU    0
#define STATE_GAME    1
#define STATE_SANDBOX 2

#define SCREENLEFT    0
#define SCREENRIGHT   64
#define SCREENTOP     128
#define SCREENBOTTOM  0
#define SCREENMID     64

#define REMAP_THRESHOLD 64

//screen dimensions in blocks
#define SCREENWIDTH   8
#define SCREENHEIGHT  16

#define BLOCKSIZE 8
#define PLAYER_WIDTH  6
#define PLAYER_HEIGHT 8

// special tile indices
#define DASH  17
#define BLOCK 18

extern Arduboy2 arduboy;
extern Sprites sprites;

extern uint8_t gameState;

extern int16_t cameraOffset;

typedef struct 
{
  int8_t x;
  int16_t y;
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
  int trim(int p, int l, int h);
}

#endif

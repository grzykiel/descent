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

#define MAPWIDTH 8
#define MAPHEIGHT 48

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



// TODO remove if unused
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

typedef struct {
  bool active = false;
  const unsigned char *sprite;
  uint8_t frame = 0;
  uint8_t t = 0;
  uint8_t last;
  uint8_t *transitions;
} sprite_t;

typedef struct {
  bool active;
  sprite_t sprite;
} particle_t;

typedef struct {
  bool active;
  uint8_t y;
  uint16_t x;
  float v = 3.2f;
  uint8_t t;
  sprite_t sprite;
} bullet_t;

typedef struct {
  uint8_t xMin;
  uint8_t xMax;
  uint8_t yMin;
  uint8_t yMax;
} window_t;

namespace Utils 
{
  int trim(int p, int l, int h);
  window_t getCollisionWindow(uint16_t x, uint8_t y);
}


#endif

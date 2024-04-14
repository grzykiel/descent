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

#define MF_OFFSET 8

extern Arduboy2 arduboy;
extern Sprites sprites;

extern uint8_t gameState;

extern int16_t cameraOffset;

const float BULLET_ACCEL = 0.16f;
const float BULLET_START_VEL = 3.2f;

const uint8_t muzzleFlashTransitions[1] = {5};
const uint8_t bulletTransitions[8] = {1, 2, 3, 5, 8, 11, 15, 20};//{1, 5, 9, 12, 15, 17, 19, 20};

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
  bool active;
  const unsigned char *sprite;
  uint8_t frame;
  uint8_t t;
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

namespace Util 
{
  int trim(int p, int l, int h);
}

#endif

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>

#define FPS 60

#define STATE_MENU    0
#define STATE_GAME    1
#define STATE_SANDBOX 2

//debug movement modes
#define TOPDOWN   0
#define PLATFORM  1

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
#define PLAYER_OFFSET 1 //sprite offset

// special tile indices
#define DASH  17
#define BLOCK 18

// Collision locations
#define NONE        0
#define RIGHT       1
#define LEFT        2
#define BOTTOM      1
#define TOP         2

// Jump
const float JUMP_GRAVITY = -0.056f;
const float JUMP_VELOCITY = 1.7F;
const float THRUST = 0.056f;
#define HALF_JUMP   15
#define JUMP_TOP    25
#define JUMPFRAMES  50
#define FALL_FRAME  4

extern Arduboy2 arduboy;
extern Sprites sprites;

extern uint8_t gameState;

extern uint8_t movementMode; //debug

extern int16_t cameraOffset;

enum class Direction : uint8_t
{
  up,
  down,
  left,
  right
};

typedef struct {
  uint8_t v;
  uint8_t h;
} collision_t;

typedef struct {
  int16_t x;
  int8_t y;
} vector_t;

typedef struct {
  const unsigned char *sprite;
  uint8_t last;
  uint8_t *transitions;

  uint8_t dx;
  uint8_t dy;
  uint8_t w;
  uint8_t h;
} sprite_t;

typedef struct {
  bool active = false;
  uint8_t frame = 0;
  uint8_t t = 0;
  uint16_t x;
  uint8_t y;
  sprite_t *sprite;
} animation_t;

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
  bool collides(animation_t anim, Rect block);
  collision_t collisionCorrect(animation_t anim, vector_t *next, Rect collider);

  bool updateAnimation(animation_t *animation);

}


#endif

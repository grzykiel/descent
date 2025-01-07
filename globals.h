#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <stdint.h>
#include "bitmaps.h"

#define FPS 60

#define STATE_MENU      0
#define STATE_GAME      1
#define STATE_DEATH     2
#define STATE_GAMEOVER  3
#define STATE_PAUSED    4

#define SCREENLEFT    0
#define SCREENRIGHT   64
#define SCREENTOP     128
#define SCREENBOTTOM  0
#define SCREENMID     64
#define WALL_OFFSET   2
#define CEILING       370*128

#define OFFSCREEN 128*128
#define PIXEL_SCALE 128

#define MAPWIDTH  8
#define MAPHEIGHT 48
#define MAPSIZE   192
#define ROOMSIZE  64

#define REMAP_THRESHOLD 64

//screen dimensions in blocks
#define SCREENWIDTH 8
#define SCREENHEIGHT 16

#define BLOCKSIZE     8

#define UPGRADE_SIZE  8

// special tile indices
#define DASH  4
#define BLOCK 1 

#define DASH_OFFSET 5
#define DASH_HEIGHT 3

// Collision locations
#define NONE    0
#define RIGHT   1
#define LEFT    2
#define BOTTOM  1
#define TOP     2

#define GRAVITY           -7
#define TERMINAL_VELOCITY -4

#define FLICKER_DURATION  5

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define G 16
#define H 17
#define I 18
#define J 19
#define K 20
#define L 21
#define M 22
#define N 23
#define O 24
#define P 25
#define Q 26
#define R 27
#define S 28
#define T 29
#define U 30
#define V 31
#define W 32
#define X 33
#define Y 34
#define Z 35
#define COLN 36
#define EXCL 37
#define QSTN 38

extern Arduboy2Base arduboy;
extern ArduboyTones sound;
extern Sprites sprites;

extern uint8_t gameState;
extern int16_t cameraOffset;
extern uint16_t score;

enum class Direction : uint8_t {
  up,
  down,
  left,
  right
};

enum class PlayerState : uint8_t {
  grounded,
  jumping,
  bouncing,
  falling
};

enum class GunType : uint8_t {
  machine,
  shot,
  laser
};

typedef struct {
  uint8_t v;
  uint8_t h;
} collision_t;

typedef struct {
  uint16_t x; 
  int16_t y;
} position_t;

typedef struct {
  int16_t x;
  int16_t y;
} velocity_t;

typedef struct {
  const unsigned char *spriteR;
  const unsigned char *spriteL;
  uint8_t last;
  uint8_t *transitions;

  uint8_t offset; // dx, dy
  uint8_t dim;    // w, h
} sprite_t;

typedef struct {
  bool active = false;
  uint8_t frame = 0;
  uint8_t t = 0;
  int8_t iframe = 0;
  position_t pos;
  velocity_t vel;
  sprite_t *sprite;
  Direction dir;
} animation_t;

typedef struct {
  bool active;
  uint8_t frame = 0;
  uint8_t t = 0;
  position_t pos;
  velocity_t vel;
} bullet_t;

typedef struct {
  bool active;
  uint8_t t;
  uint8_t frame;
  position_t pos;
} particle_t;

typedef struct {
  bool active;
  position_t pos;
} powerup_t;

typedef struct {
  uint8_t type;
  position_t pos;
} upgrade_t;

typedef struct {
  uint8_t xMin;
  uint8_t xMax;
  uint8_t yMin;
  uint8_t yMax;
} window_t;

namespace Utils {
int trim(int p, int l, int h);
int sign(int x);

window_t getCollisionWindow(position_t pos);
window_t getCollisionWindow(uint16_t x, int16_t y);
bool collides(animation_t anim, Rect block);
bool collides(animation_t anim1, animation_t anim2);
collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider);

bool updateAnimation(animation_t *animation);
bool updateAnimation(particle_t *particle, uint8_t *transitions, uint8_t last);
bool flickering(int8_t *f);

void printNum(uint8_t x, uint8_t y, uint16_t n, uint8_t length);
void printText(uint8_t x, uint8_t y, uint8_t *text, uint8_t length);

}


#endif

#ifndef PLAYER_H
#define PLAYER_H
// #include "enums.h"
#include "levels.h"

struct player_t {
  int8_t y;
  int8_t x;
  int8_t vy;
  int8_t vx;
  Direction dir;
  const unsigned char *sprite;
  uint8_t frame;
};

extern player_t player;

extern player_t playerNext;
#endif


namespace Player {
void update();
void draw();
void init();
}







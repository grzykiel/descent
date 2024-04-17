#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"

typedef struct {
  int8_t y;
  int16_t x;
  int8_t vy;
  int8_t vx;
  Direction dir;
  const unsigned char *sprite;
  uint8_t frame;
} player_t;

extern player_t player;
extern player_t playerNext;

extern const int8_t walkSpeed;
extern const uint8_t walkAnimDelay;



#endif


namespace Player {

void update();
void draw();

void collisionCheck();
void collisionCorrect(Rect collision);

void init();
void initPlayer();



}

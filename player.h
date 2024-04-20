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

  // TODO remove if superseded by sprite_t
  const unsigned char *sprite;
  uint8_t frame; 

} player_t;

/* typedef struct {
  animation_t animation = {
    .active = false,
    .frame = 0,
    .t = 0,
    .x = SCREENMID + 128,
    .y = 28,
    .sprite = {
      .sprite = Player::runRightSprite,
      .last = null, // change for jumping
      .transitions = null, // change for jumping
      .dx = 0,
      .dy = 1,
      .w = 6,
      .h = 8
    }
  }

  Direction dir;
  
  int8_t vx;
  int8_t vy;

} player_t */

extern player_t player;
extern player_t playerNext;
extern sprite_t playerSprite;

extern const int8_t walkSpeed;
extern const uint8_t walkAnimDelay;

#endif


namespace Player {
  void update();
  void draw();

  void collisionCheck();
  void collisionCorrect(Rect collision);
  uint8_t collisionCorrection(Rect collider); // TODO remove
  //TODO vector_t collisionCorrection(animation_t anim, vector_t next, Rect collider)

  void init();
  void initPlayer();
}

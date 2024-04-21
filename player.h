#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"


typedef struct {
  int8_t y = 28; //TODO remove
  int16_t x = 192;

  int8_t vx;
  int8_t vy;

  Direction dir;

  animation_t animation;

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

  uint8_t checkCollisions(animation_t anim, vector_t *next);
  uint8_t collisionCorrect(animation_t anim, vector_t *next, Rect collider);

  /*
  void collisionCheck(); // TODO replace with checkCollisions();
  

  void collisionCorrect(Rect collision); //TODO replace with correctCollision
  void correctCollision(animation_t anim, vector_t *next, Rect collider); //TODO move to game
  */



  void init();
  void initPlayer();
}

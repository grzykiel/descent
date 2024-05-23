#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"


typedef struct {
  Direction dir;

  animation_t animation;

  bool grounded = false;

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
  
  float vx;
  float vy;

} player_t */

extern player_t player;

//TODO remove
// extern player_t playerNext; 
// extern sprite_t playerSprite;


extern const int8_t walkSpeed;
extern const uint8_t walkAnimDelay;


#endif


namespace Player {
  void init();
  void update();
  void draw();

  void updateAnimation();
  // void initPlayer();

  void jump();
  void fall();
  void thrust();
  void land();

  collision_t checkTileCollisions(animation_t anim, position_t *next);
  void checkEnemyCollisions(animation_t anim, position_t *next);
}

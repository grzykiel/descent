#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"


typedef struct {
  // Direction dir;

  animation_t animation;

  // bool grounded = false;
  PlayerState state = PlayerState::falling;

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

extern const int8_t walkSpeed;
extern const uint8_t walkAnimDelay;


#endif


namespace Player {
  void init();
  void update();
  void draw();

  void updateAnimation();
  // void initPlayer();

  void run(Direction dir);
  void jump();
  void fall();
  void thrust();
  void bounce();
  void land();
  void stop();

  void flicker();

  void checkTileCollisions(position_t *nextPos, velocity_t *nextVel);
  void checkEnemyCollisions(position_t *nextPos, velocity_t *nextVel);
}

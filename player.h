#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"
#include "hud.h"

#include "game.h"
#include "bitmaps.h"
#include "enemies.h"
#include "bullet.h"

#define HP_CAP 5
#define HP_INIT 3

typedef struct {
  // Direction dir;

  animation_t animation;

  PlayerState state = PlayerState::falling;

  uint8_t hp;

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


#endif


namespace Player {
  void init();
  void update();
  void draw();

  void updateAnimation();

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
  void checkPowerupCollisions(position_t nextPos);

  void onDamaged(); 
  void onPickupHeart();
  void onPickupHeartUpgrade();
}

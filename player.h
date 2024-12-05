#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "globals.h"
#include "hud.h"
#include "game.h"
#include "bitmaps.h"
#include "enemies.h"
#include "bullet.h"
#include "sound.h"

#define HP_INIT      3
#define HP_CAP       5
#define N_WALKFRAMES 4

typedef struct {
  animation_t animation;
  PlayerState state = PlayerState::falling;
  uint8_t hp;
} player_t;

extern player_t player;
extern uint8_t combo;
extern uint8_t power;

#endif


namespace Player {
  void init();
  void update();
  void draw();

  void updateAnimation();

  void run(Direction dir);
  void jump();
  void fall();
  void thrust(uint8_t multiplier);
  void bounce();
  void land();
  void stop();

  void flicker();

  void checkTileCollisions(position_t *nextPos, velocity_t *nextVel);
  void checkEnemyCollisions(position_t *nextPos, velocity_t *nextVel);
  void checkPowerupCollisions(position_t nextPos);

  void onDamaged(); 
  void onPickup(uint8_t p);

  void resetCombo();
  void increaseCombo();
  void onComboEnd();

  void increasePower(uint8_t p);
  void resetPower();

}

#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"

#define MAX_BULLETS 5
#define BULLET_ACCEL 20
#define BULLET_START_VEL 410
#define FIRE_RATE 15

const uint8_t muzzleFlashTransitions[] = {5};
extern sprite_t muzzleFlashSprite;
extern animation_t muzzleFlash;
extern uint8_t shootTimer;
extern bool triggerReleased;

extern sprite_t bulletSprite;
extern animation_t bulletAnim;
extern animation_t bullet[MAX_BULLETS];
extern uint8_t capacity;
extern uint8_t bulletsRemaining;
extern uint8_t chamber;

const uint8_t bulletTransitions[] = {1, 2, 3, 5, 8, 11, 15}; //, 20};

namespace Bullet {
  void init();
  void update();
  void draw();

  void shoot();
  void reload();

  void initMuzzleFlash();
  void drawMuzzleFlash();

  void initBullets();
  void updateBullets();
  void collisionCheck();
  void drawBullets();

  void drawAmmo();
}

#endif
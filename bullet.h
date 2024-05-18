#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"

typedef struct {
  animation_t animation;
  float v = 3.2f;
} bullet_t;

#define MAX_BULLETS 5

const uint8_t muzzleFlashTransitions[1] = {5};
extern sprite_t muzzleFlashSprite;
extern animation_t muzzleFlash;

extern sprite_t bulletSprite;
extern animation_t bulletAnim;
extern bullet_t bullet[MAX_BULLETS];
extern uint8_t bulletsUsed;
extern uint8_t chamber;

const uint8_t bulletTransitions[7] = {1, 2, 3, 5, 8, 11, 15}; //, 20};

const float BULLET_ACCEL = 0.16f;
const float BULLET_START_VEL = 3.2f;

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
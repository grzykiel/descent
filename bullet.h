#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"

#define MF_OFFSET 8

#define BULLET_SIZE 4
#define BULLET_OFFSET 2
#define BULLET_FRAME_LAST 8

#define MAX_BULLETS 5

extern particle_t muzzleFlash;

extern bullet_t bullet[5];
extern uint8_t bulletsUsed;
extern uint8_t chamber;


const uint8_t muzzleFlashTransitions[1] = {5};
const uint8_t bulletTransitions[8] = {1, 2, 3, 5, 8, 11, 15, 20};

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
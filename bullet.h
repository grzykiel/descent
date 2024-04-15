#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"

#define MF_OFFSET 8

extern particle_t muzzleFlash;

const uint8_t muzzleFlashTransitions[1] = {5};
const uint8_t bulletTransitions[8] = {1, 2, 3, 5, 8, 11, 15, 20};

const float BULLET_ACCEL = 0.16f;
const float BULLET_START_VEL = 3.2f;


namespace Bullet {
  void init();
  void update();
  void draw();

  void shoot();

  void initMuzzleFlash();
  void drawMuzzleFlash();

  void initBullets();
  void updateBullets();
  void drawBullets();
}
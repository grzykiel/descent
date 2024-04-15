#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"

#define MF_OFFSET 8

extern particle_t muzzleFlash;

const uint8_t muzzleFlashTransitions[1] = {5};

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
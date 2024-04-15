#include "bullet.h"

particle_t muzzleFlash;

namespace Bullet {
void init() {
  initMuzzleFlash();
}

void update() {
  
}

void draw() {
  drawMuzzleFlash();
}

void shoot() {
  muzzleFlash.active = true;
  muzzleFlash.sprite.t = 0;
  muzzleFlash.sprite.frame = 0;
}

void initMuzzleFlash() {
  muzzleFlash.active = false;
  muzzleFlash.sprite.sprite = ShootShoes::muzzleFlash;
  muzzleFlash.sprite.transitions = muzzleFlashTransitions;
  muzzleFlash.sprite.last = 1;
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.x - cameraOffset - MF_OFFSET, player.y, muzzleFlash.sprite.sprite, muzzleFlash.sprite.frame);
    muzzleFlash.active = Game::updateSprite(&muzzleFlash.sprite);
  }
}
}
#include "bullet.h"

particle_t muzzleFlash;

namespace Bullet {
void init() {
  initMuzzleFlash();
  initBullets();
}

void update() {
  updateBullets();
}

void draw() {
  drawMuzzleFlash();
  drawBullets();
}

void shoot() {
  muzzleFlash.active = true;
  muzzleFlash.sprite.t = 0;
  muzzleFlash.sprite.frame = 0;

  bullet.active = true;
  bullet.x = player.x;
  bullet.y = player.y;
  bullet.sprite.frame = 0;
  bullet.sprite.t = 0;
  bullet.t = 0;
  bullet.v = BULLET_START_VEL;
}

void initMuzzleFlash() {
  muzzleFlash.active = false;
  muzzleFlash.sprite.sprite = ShootShoes::muzzleFlash;
  muzzleFlash.sprite.transitions = muzzleFlashTransitions;
  muzzleFlash.sprite.last = 1;  //TODO #define
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.x - cameraOffset - MF_OFFSET, player.y, muzzleFlash.sprite.sprite, muzzleFlash.sprite.frame);
    muzzleFlash.active = Game::updateSprite(&muzzleFlash.sprite);
  }
}

void initBullets() {
  // init bullet
  bullet.active = false;
  bullet.sprite.sprite = ShootShoes::bullet;
  bullet.sprite.transitions = bulletTransitions;
  bullet.sprite.last = 8;  //TODO #define
}

void updateBullets() {
  if (bullet.active) {
    bullet.x = int(1.0f * bullet.x - bullet.v);
    bullet.v -= BULLET_ACCEL;
    bullet.active = Game::updateSprite(&bullet.sprite);
  }
}

void drawBullets() {
  if (bullet.active) {
    Sprites::drawSelfMasked(bullet.x - cameraOffset, bullet.y, bullet.sprite.sprite, bullet.sprite.frame);
  }
}
}
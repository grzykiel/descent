#include "bullet.h"

sprite_t muzzleFlashSprite = {
  ShootShoes::muzzleFlash,  //sprite
  nullptr,
  0,                       //last frame
  muzzleFlashTransitions,  //frame transitions
  8,                       //dx
  0,                       //dy
  8,                       //w
  8,                       //h
};
animation_t muzzleFlash;

sprite_t bulletSprite = {
  ShootShoes::bullet,  //sprite
  nullptr,
  6,                  //last frame
  bulletTransitions,  //frame transitions
  0,                  //dx
  2,                  //dy
  4,                  //w
  4,                  //h
};

bullet_t bullet[5];
// TODO include in initBullets()
uint8_t bulletCapacity = MAX_BULLETS;
uint8_t bulletsRemaining = bulletCapacity;
uint8_t chamber = 0;

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
  drawAmmo();
}

void shoot() {
  if (bulletsRemaining > 0) {
    Player::thrust();

    muzzleFlash.active = true;
    muzzleFlash.t = 0;
    muzzleFlash.frame = 0;

    bullet[chamber].animation.active = true;
    bullet[chamber].animation.pos.x = player.animation.pos.x;
    bullet[chamber].animation.pos.y = player.animation.pos.y;
    bullet[chamber].animation.vel.x = BULLET_START_VEL;
    bullet[chamber].animation.vel.y = player.animation.vel.y;
    bullet[chamber].animation.frame = 0;
    bullet[chamber].animation.t = 0;
    chamber = (chamber + 1) % MAX_BULLETS;

    bulletsRemaining--;
    HUD::onShoot();
  } else {

  }
}

void reload() {
  bulletsRemaining = bulletCapacity;
}

void initMuzzleFlash() {
  muzzleFlash.active = false;
  muzzleFlash.frame = 0;
  muzzleFlash.t = 0;
  muzzleFlash.sprite = &muzzleFlashSprite;
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset - muzzleFlash.sprite->dx, player.animation.pos.y / PIXEL_SCALE, muzzleFlash.sprite->spriteR, muzzleFlash.frame);
    muzzleFlash.active = Utils::updateAnimation(&muzzleFlash);
  }
}

void initBullets() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullet[i].animation.sprite = &bulletSprite;
    bullet[i].animation.active = false;
    bullet[i].animation.frame = 0;
    bullet[i].animation.t = 0;
  }
}

void updateBullets() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].animation.active) {
      bullet[i].animation.pos.x -= bullet[i].animation.vel.x;
      bullet[i].animation.vel.x -= BULLET_ACCEL;
      bullet[i].animation.active = Utils::updateAnimation(&bullet[i].animation);
    }
  }

  collisionCheck();
}

void collisionCheck() {
  for (int b = 0; b < MAX_BULLETS; b++) {
    if (!bullet[b].animation.active) continue;

    // window_t wd = Utils::getCollisionWindow(bullet[b].animation.pos.x/PIXEL_SCALE, bullet[b].animation.pos.y/PIXEL_SCALE);
    window_t wd = Utils::getCollisionWindow(bullet[b].animation.pos);

    for (int i = wd.xMin; i <= wd.xMax; i++) {
      for (int j = wd.yMin; j <= wd.yMax; j++) {
        if (levelMap[i][j]) {
          if (levelMap[i][j] != DASH) {
            Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
            if (Utils::collides(bullet[b].animation, blockRect)) {
              bullet[b].animation.active = false;
              if (levelMap[i][j] == BLOCK) {
                levelMap[i][j] = 0;
                Particles::spawnBlockFragment(i, j);
              }
            }
          }
        }
      }
    }
  }
}

void drawBullets() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].animation.active) {
      Sprites::drawSelfMasked(bullet[i].animation.pos.x / PIXEL_SCALE - cameraOffset, bullet[i].animation.pos.y / PIXEL_SCALE, bullet[i].animation.sprite->spriteR, bullet[i].animation.frame);
    }
  }
}

// DEBUG
void drawAmmo() {
  // arduboy.setCursor(player.animation.pos.x + 9 - cameraOffset, player.animation.pos.y);
  // arduboy.print(bulletsRemaining);
}
}
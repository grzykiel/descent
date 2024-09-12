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
animation_t muzzleFlash;  //TODO make particle_t

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

animation_t bullet[5];
uint8_t shootTimer;
bool triggerReleased;

animation_t bulletAnim;
uint8_t bulletCapacity;
uint8_t bulletsRemaining;
uint8_t chamber = 0;

uint8_t bulletAccel;
uint16_t bulletV0;
uint8_t fireRate;

namespace Bullet {
void init() {
  initMuzzleFlash();
  initBullets();

  shootTimer = 0;
  triggerReleased = false;
  bulletCapacity = AMMO_INIT;
  bulletsRemaining = AMMO_INIT;

  bulletAccel = BULLET_ACCEL_INITIAL;
  bulletV0 = BULLET_V0_INITIAL;
  fireRate = FIRE_RATE_INITIAL;
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
  if (shootTimer > 0) {
    shootTimer--;
  } else if (shootTimer == 0) {
    if (bulletsRemaining > 0) {
      Player::thrust();

      muzzleFlash.active = true;
      muzzleFlash.t = 0;
      muzzleFlash.frame = 0;

      bullet[chamber].active = true;
      bullet[chamber].pos.x = player.animation.pos.x;
      bullet[chamber].pos.y = player.animation.pos.y;
      bullet[chamber].vel.x = bulletV0;  //BULLET_START_VEL;
      bullet[chamber].vel.y = player.animation.vel.y;
      bullet[chamber].frame = 0;
      bullet[chamber].t = 0;
      chamber = (chamber + 1) % AMMO_CAP;

      bulletsRemaining--;
      HUD::onShoot();

      shootTimer = fireRate;
    } else {
      Particles::spawnSmoke();
    }
  }
}

void reload() {
  if (bulletsRemaining < bulletCapacity) {
    bulletsRemaining = bulletCapacity;
    Particles::activateRecharge();
    HUD::onRecharge();
  }
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
  for (int i = 0; i < AMMO_CAP; i++) {
    bullet[i].sprite = &bulletSprite;
    bullet[i].active = false;
    bullet[i].frame = 0;
    bullet[i].t = 0;
  }
}

void updateBullets() {
  for (int i = 0; i < AMMO_CAP; i++) {
    if (bullet[i].active) {
      bullet[i].pos.x -= bullet[i].vel.x;
      bullet[i].vel.x -= bulletAccel;
      bullet[i].active = Utils::updateAnimation(&bullet[i]);
    }
  }

  collisionCheck();
}

void collisionCheck() {
  for (int b = 0; b < AMMO_CAP; b++) {
    if (!bullet[b].active) continue;

    // window_t wd = Utils::getCollisionWindow(bullet[b].pos.x/PIXEL_SCALE, bullet[b].animation.pos.y/PIXEL_SCALE);
    window_t wd = Utils::getCollisionWindow(bullet[b].pos);

    for (int i = wd.xMin; i <= wd.xMax; i++) {
      for (int j = wd.yMin; j <= wd.yMax; j++) {
        if (!levelMap[i][j]) continue;
        if (levelMap[i][j] != DASH) {
          Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
          if (Utils::collides(bullet[b], blockRect)) {
            bullet[b].active = false;
            bullet[b].pos.x = blockRect.x * PIXEL_SCALE;
            if (levelMap[i][j] == BLOCK) {
              Level::destroyBlock(i, j);
            } else {
              Particles::spawnClink(bullet[b].pos, 8, 2);
            }
          }
        }
      }
    }
  }
}

void drawBullets() {
  for (uint8_t i = 0; i < AMMO_CAP; i++) {
    if (bullet[i].active) {
      Sprites::drawSelfMasked(bullet[i].pos.x / PIXEL_SCALE - cameraOffset, bullet[i].pos.y / PIXEL_SCALE, bullet[i].sprite->spriteR, bullet[i].frame);
    }
  }
}

void onShiftMap() {
  for (uint8_t i = 0; i < AMMO_CAP; i++) {
    if (bullet[i].active) Level::shiftPos(&bullet[i].pos);
  }
}

void decreaseFireRate() {
  fireRate = max(fireRate - 1, FIRE_RATE_MIN);
}

// DEBUG
void increaseFireRate() {
  fireRate = min(fireRate + 1, 30);
}

void drawAmmo() {
  // arduboy.setCursor(player.animation.pos.x + 9 - cameraOffset, player.animation.pos.y);
  // arduboy.print(bulletsRemaining);
}
}
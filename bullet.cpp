#include "bullet.h"

sprite_t muzzleFlashSprite = {
  ShootShoes::muzzleFlash,  //sprite
  nullptr,
  0,                       //last frame
  muzzleFlashTransitions,  //frame transitions
  8,                       //dx
  0,                       //dy
  0x88
};
animation_t muzzleFlash;  //TODO make particle_t

sprite_t bulletSprite = {
  ShootShoes::bullet,  //sprite
  nullptr,
  6,                  //last frame
  bulletTransitions,  //frame transitions
  0,                  //dx
  2,                  //dy
  0x44
};

animation_t bullet[MAX_AMMO];
uint8_t shootTimer;
bool triggerReleased;

animation_t bulletAnim;
uint8_t bulletCapacity;
uint8_t bulletsRemaining;
uint8_t chamber = 0;

uint8_t bulletAccel;
uint16_t bulletV0;
uint8_t fireRate;

GunType activeGun = GunType::automatic;

namespace Bullet {
void init() {
  initMuzzleFlash();
  initBullets();

  shootTimer = 0;
  triggerReleased = false;
  bulletCapacity = AMMO_INIT;
  bulletsRemaining = AMMO_INIT;

  bulletAccel = BULLET_ACCEL_INIT;
  bulletV0 = BULLET_V0_INIT;
  fireRate = FIRE_RATE_INIT;
}

void update() {
  if (activeGun == GunType::automatic || activeGun == GunType::shot) {
    updateBullets();
  } else if (activeGun == GunType::laser) {
    updateLaser();
  }
}


void draw() {
  if (activeGun == GunType::automatic || activeGun == GunType::shot) {
    drawBullets();
  } else if (activeGun == GunType::laser) {
    drawLaser();
  }
  drawMuzzleFlash();
}

void shoot() {
  if (activeGun == GunType::automatic) {
    fireAuto();
  } else if (activeGun == GunType::laser) {
    fireLaser();
  } else if (activeGun == GunType::shot) {
    fireShotgun();
  }
}

void fireAuto() {
  if (shootTimer > 0) {
    shootTimer--;
  } else { // if (shootTimer == 0) {
    if (bulletsRemaining > 0) {
      Player::thrust(BULLET_THRUST_SCALE);

      muzzleFlash.active = true;
      muzzleFlash.t = 0;
      muzzleFlash.frame = 0;

      bullet[chamber].active = true;
      bullet[chamber].pos.x = player.animation.pos.x;
      bullet[chamber].pos.y = player.animation.pos.y;
      bullet[chamber].vel.x = bulletV0;
      bullet[chamber].vel.y = player.animation.vel.y;
      bullet[chamber].frame = 0;
      bullet[chamber].t = 0;
      chamber = (chamber + 1) % MAX_AMMO;

      bulletsRemaining--;
      HUD::onShoot();

      shootTimer = fireRate;
    } else {
      Particles::spawnSmoke();
    }
  }
}

void fireLaser() {
  if (bullet[chamber].active) return;
  if (bulletsRemaining > 0) {
    bullet[chamber].active = true;
    bullet[chamber].t = LASER_TIME;
    Player::thrust(LASER_THRUST_SCALE);

    muzzleFlash.active = true;
    muzzleFlash.t = 0;
    muzzleFlash.frame = 0;

    bulletsRemaining--;
    HUD::onShoot();
  }
}

void fireShotgun() {
  if (bulletsRemaining == 0) return;
  for (uint8_t i = 0; i < N_SHOTS; i++) {
    bullet[chamber].active = true;
    bullet[chamber].pos.x = player.animation.pos.x;
    bullet[chamber].pos.y = player.animation.pos.y;
    bullet[chamber].vel.x = (uint8_t)pgm_read_word(&shotVelocitiesX[i]);//SHOT_V0_INIT;
    bullet[chamber].vel.y = (int8_t)pgm_read_word(&shotVelocitiesY[i]);
    bullet[chamber].frame = 0;
    bullet[chamber].t = 0;
    chamber = (chamber + 1) % MAX_AMMO;
  }
  Player::thrust(SHOT_THRUST_SCALE);
  bulletsRemaining--;
  HUD::onShoot();
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
  for (int i = 0; i < MAX_AMMO; i++) {
    bullet[i].sprite = &bulletSprite;
    bullet[i].active = false;
    bullet[i].frame = 0;
    bullet[i].t = 0;
  }
}

void updateBullets() {
  for (int i = 0; i < MAX_AMMO; i++) {
    if (bullet[i].active) {
      bullet[i].pos.x -= bullet[i].vel.x;
      if (activeGun == GunType::shot) {
        bullet[i].pos.y -= bullet[i].vel.y;
        bullet[i].vel.x -= SHOT_ACCEL_INIT;
      } else {
        bullet[i].vel.x -= bulletAccel;
      }
      bullet[i].active = Utils::updateAnimation(&bullet[i]);
    }
  }
  collisionCheck();
}

void updateLaser() {
  if (bullet[chamber].active) {
    bullet[chamber].t--;
    if (bullet[chamber].t == 0) {
      bullet[chamber].active = false;
    }
  }
}

void collisionCheck() {
  for (uint8_t b = 0; b < MAX_AMMO; b++) {
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
  for (uint8_t i = 0; i < MAX_AMMO; i++) {
    if (bullet[i].active) {
      Sprites::drawSelfMasked(bullet[i].pos.x / PIXEL_SCALE - cameraOffset, bullet[i].pos.y / PIXEL_SCALE, bullet[i].sprite->spriteR, bullet[i].frame);
    }
  }
}

void drawLaser() {
  if (bullet[chamber].t == 0) return;

  uint8_t x1 = player.animation.pos.x / PIXEL_SCALE;
  uint8_t y0 = player.animation.pos.y / PIXEL_SCALE + BLOCKSIZE/2 - LASER_WIDTH_INIT/2;
  uint8_t y1 = y0 + LASER_WIDTH_INIT;
  uint8_t x0 = x1 - BLOCKSIZE;

  uint8_t i_x = player.animation.pos.x / PIXEL_SCALE / BLOCKSIZE;
  i_x = MAPHEIGHT - i_x - 1;
  uint8_t i_y = player.animation.pos.y / PIXEL_SCALE / BLOCKSIZE;
  Rect laserRect = Rect(x0, y0, x1 - x0, y1 - y0);
  bool collides = false;
  for (uint8_t i = i_x; i < i_x + 8; i++) {

    
    if (Enemies::checkLaserCollisions(laserRect)) {
      x0 += 4;
      Particles::spawnClink(x0, y0, 0, 0);
      break;
    }

    for (uint8_t j = i_y; j <= i_y + 1; j++) {
      if (j >= SCREENWIDTH) continue;
      if (!levelMap[i][j] || levelMap[i][j] == DASH) continue;

      Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
      if (arduboy.collide(laserRect, blockRect)) {
        if (levelMap[i][j] == BLOCK) {
          Level::destroyBlock(i, j);
        } else {
          collides = true;
          x0 = (MAPHEIGHT - i) * BLOCKSIZE;
          Particles::spawnExplosion(x0, y0, 0, 0);
          break;
        }
      }
    }
    if (collides) break;
    x0 -= BLOCKSIZE;  // TODO refactor to laserRect.x
    laserRect = Rect(x0, y0, x1 - x0, y1 - y0);
  }
  arduboy.fillRect(x0 - cameraOffset, y0, x1 - x0, y1 - y0);
}

void onShiftMap() {
  for (uint8_t i = 0; i < MAX_AMMO; i++) {
    if (bullet[i].active) Level::shiftPos(&bullet[i].pos);
  }
}

void setActiveGun(GunType newType) {
  init();
  activeGun = newType;
}

void increaseCap() {
  bulletCapacity = min(++bulletCapacity, MAX_AMMO);
}

void decreaseFireRate() {
  fireRate = max(fireRate - 1, FIRE_RATE_MIN);
}

// DEBUG
void increaseFireRate() {
  fireRate = min(fireRate + 1, 30);
}
}
#include "bullet.h"

sprite_t muzzleFlashSprite = {
  ShootShoes::muzzleFlash,  //sprite
  nullptr,
  0,                       //last frame
  muzzleFlashTransitions,  //frame transitions
  0x80,                    // offsets
  0x88                     // dim
};
animation_t muzzleFlash;  //TODO make particle_t

sprite_t bulletSprite = {
  ShootShoes::bullet,  //sprite
  nullptr,
  6,                  //last frame
  bulletTransitions,  //frame transitions
  0x02,
  0x44
};

bullet_t bullet[MAX_AMMO];
uint8_t shootTimer;
bool triggerReleased;

uint8_t bulletCapacity;
uint8_t bulletsRemaining;
uint8_t chamber = 0;

uint8_t fireRate;

GunType activeGun;

namespace Bullet {
void init() {
  initMuzzleFlash();
  initBullets();

  shootTimer = 0;
  triggerReleased = false;
  bulletCapacity = AMMO_INIT;
  bulletsRemaining = AMMO_INIT;

  fireRate = FIRE_RATE_INIT;

  activeGun = GunType::machine;
}

void update() {
  if (activeGun == GunType::machine || activeGun == GunType::shot) {
    updateBullets();
  } else if (activeGun == GunType::laser) {
    updateLaser();
  }
}


void draw() {
  if (activeGun == GunType::machine || activeGun == GunType::shot) {
    drawBullets();
  } else if (activeGun == GunType::laser) {
    drawLaser();
  }
  drawMuzzleFlash();
}

void shoot() {
  if (activeGun == GunType::machine) {
    fireAuto();
  } else if (activeGun == GunType::laser) {
    fireLaser();
  } else if (activeGun == GunType::shot) {
    fireShotgun();
  }
}

void activateMuzzleFlash() {
  muzzleFlash.active = true;
  muzzleFlash.t = 0;
  muzzleFlash.frame = 0;
}

void fireAuto() {
  if (shootTimer > 0) {
    shootTimer--;
  } else {
    if (bulletsRemaining > 0) {
      Player::thrust(BULLET_THRUST_SCALE);

      activateMuzzleFlash();

      bullet[chamber].active = true;
      bullet[chamber].pos.x = player.animation.pos.x;
      bullet[chamber].pos.y = player.animation.pos.y;
      bullet[chamber].vel.x = BULLET_V0 + 99 * power;
      bullet[chamber].vel.y = player.animation.vel.y;
      bullet[chamber].frame = 0;
      bullet[chamber].t = 0;
      chamber = (chamber + 1) % MAX_AMMO;

      bulletsRemaining--;
      if (bulletsRemaining == 0) HUD::onEmpty();
      Sound::playTone(110, 3);

      shootTimer = FIRE_RATE_INIT - 4 * power;  //fireRate;
    } else {
      onEmpty();
    }
  }
}

void fireLaser() {
  if (bullet[chamber].active) return;

  if (bulletsRemaining < (power + LASER_CHARGES)) {
    onEmpty();
    return;
  }

  bullet[chamber].active = true;
  bullet[chamber].t = LASER_TIME;
  Player::thrust(LASER_THRUST_SCALE);

  activateMuzzleFlash();

  bulletsRemaining -= (power + LASER_CHARGES);
  Sound::playSweep(2400, 40, 15);
}

void fireShotgun() {
  if (bulletsRemaining < SHOT_CHARGES) {
    onEmpty();
    return;
  }

  activateMuzzleFlash();
  for (uint8_t i = 0; i < N_SHOTS; i++) {
    bullet[chamber].active = true;
    bullet[chamber].pos.x = player.animation.pos.x;
    bullet[chamber].pos.y = player.animation.pos.y;

    if (i < 3) {
      bullet[chamber].vel.x = (int16_t)pgm_read_word(&shotVelocitiesX[i]) + 51 * power;
      if (i == 0) {
        bullet[chamber].vel.y = 0;
      } else {
        bullet[chamber].vel.y = (int8_t)pgm_read_word(&shotVelocitiesY[i]) + 10 * power;
      }
    } else {
      bullet[chamber].vel.x = (int16_t)pgm_read_word(&shotVelocitiesX[i - 2]) + 51 * power;
      bullet[chamber].vel.y = -(int8_t)pgm_read_word(&shotVelocitiesY[i - 2]) - 10 * power;
    }

    bullet[chamber].frame = 0;
    bullet[chamber].t = 0;
    chamber = (chamber + 1) % MAX_AMMO;
  }
  Player::thrust(SHOT_THRUST_SCALE);
  bulletsRemaining -= SHOT_CHARGES;
  Sound::playNoise(20, 400, 15); //(200, 1600, 15);
}

void reload() {
  if (bulletsRemaining < bulletCapacity) {
    bulletsRemaining = bulletCapacity;
    Particles::activateRecharge();
  } else if (combo > 4) {
    Particles::activateRecharge();
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
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset - ((muzzleFlash.sprite->offset & 0xF0) >> 4), player.animation.pos.y / PIXEL_SCALE, muzzleFlash.sprite->spriteR, muzzleFlash.frame);
    muzzleFlash.active = Utils::updateAnimation(&muzzleFlash);
  }
}

bool updateBulletAnimation(bullet_t *bullet) {
  bullet->t++;
  if (bullet->t == (uint8_t)pgm_read_word(&bulletSprite.transitions[bullet->frame])) {
    if (bullet->frame < bulletSprite.last) {
      bullet->frame++;
    } else {
      return false;
    }
  }
  return true;
}

void initBullets() {
  for (int i = 0; i < MAX_AMMO; i++) {
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
        bullet[i].vel.x -= (10 + 3 * power);
      } else {
        bullet[i].vel.x -= (26 + 5 * power);
      }
      bullet[i].active = updateBulletAnimation(&bullet[i]);  //Utils::updateAnimation(&bullet[i]);
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
        if (Level::getMap(i, j) == 0) continue;
        if (Level::getMap(i, j) != DASH) {
          Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
          Rect bulletRect = Rect(bullet[b].pos.x / PIXEL_SCALE + ((bulletSprite.offset & 0xF0) >> 4), bullet[b].pos.y / PIXEL_SCALE + (bulletSprite.offset & 0x0F), bulletSprite.dim & 0x0F, (bulletSprite.dim & 0xF0) >> 4);

          if (arduboy.collide(bulletRect, blockRect)) {
            bullet[b].active = false;
            bullet[b].pos.x = blockRect.x * PIXEL_SCALE;
            if (Level::getMap(i, j) == BLOCK) {
              Level::destroyBlock(i, j);
              if (activeGun == GunType::shot) bullet[b].active = true;
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
      Sprites::drawSelfMasked(bullet[i].pos.x / PIXEL_SCALE - cameraOffset, bullet[i].pos.y / PIXEL_SCALE, bulletSprite.spriteR, bullet[i].frame);
    }
  }
}

void drawLaser() {
  if (bullet[chamber].t == 0) return;

  uint8_t x1 = player.animation.pos.x / PIXEL_SCALE;
  uint8_t y0 = player.animation.pos.y / PIXEL_SCALE + BLOCKSIZE / 2 - (LASER_WIDTH_INIT + 2 * power) / 2;
  uint8_t y1 = y0 + (LASER_WIDTH_INIT + 2 * power);
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
      if (Level::getMap(i, j) == 0 || Level::getMap(i, j) == DASH) continue;

      Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
      if (arduboy.collide(laserRect, blockRect)) {
        if (Level::getMap(i, j) == BLOCK) {
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

void onEmpty() {
  Particles::spawnSmoke();
  Sound::playTone(100, 3);
}

void onShiftMap() {
  for (uint8_t i = 0; i < MAX_AMMO; i++) {
    if (bullet[i].active) Level::shiftPos(&bullet[i].pos);
  }
}

void setActiveGun(GunType newType) {
  initBullets();
  if (activeGun == newType) {
    Player::increasePower(0);
  } else {
    activeGun = newType;
  }
}

void increaseCap() {
  bulletCapacity = min(bulletCapacity + 1, MAX_AMMO);
}

}
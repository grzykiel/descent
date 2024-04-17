#include "bullet.h"

particle_t muzzleFlash;

// bullet_t bullet;

bullet_t bullet[5];
uint8_t bulletsUsed = 0;
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
  if (bulletsUsed < MAX_BULLETS) {
    muzzleFlash.active = true;
    muzzleFlash.sprite.t = 0;
    muzzleFlash.sprite.frame = 0;

    bullet[chamber].active = true;
    bullet[chamber].x = player.x;
    bullet[chamber].y = player.y;
    bullet[chamber].sprite.frame = 0;
    bullet[chamber].sprite.t = 0;
    bullet[chamber].t = 0;
    bullet[chamber].v = BULLET_START_VEL;
    chamber = (chamber + 1) % MAX_BULLETS;

    bulletsUsed++;
  }
}

void reload() {
  bulletsUsed = 0;
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
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullet[i].active = false;
    bullet[i].sprite.sprite = ShootShoes::bullet;
    bullet[i].sprite.transitions = bulletTransitions;
    bullet[i].sprite.last = BULLET_FRAME_LAST;
  }
}

void updateBullets() {
  collisionCheck();
  /*if (bullet.active) {
    bullet.x = int(1.0f * bullet.x - bullet.v);
    bullet.v -= BULLET_ACCEL;
    bullet.active = Game::updateSprite(&bullet.sprite);
  }*/
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].active) {
      bullet[i].x = int(1.0f * bullet[i].x - bullet[i].v);
      bullet[i].v -= BULLET_ACCEL;
      bullet[i].active = Game::updateSprite(&bullet[i].sprite);
    }
  }
}

void collisionCheck() {
  for (int b = 0; b < MAX_BULLETS; b++) {
    window_t wd = Utils::getCollisionWindow(bullet[b].x, bullet[b].y);

    for (int i = wd.xMin; i <= wd.xMax; i++) {
      for (int j = wd.yMin; j <= wd.yMax; j++) {
        if (levelMap[i][j]) {
          if (levelMap[i][j] != DASH) {
            Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
            Rect bulletRect = Rect(bullet[b].x, bullet[b].y + BULLET_OFFSET, BULLET_SIZE, BULLET_SIZE);
            if (arduboy.collide(bulletRect, blockRect)) {
              bullet[b].active = false;
              if (levelMap[i][j] == BLOCK) {
                levelMap[i][j] = 0;
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
    if (bullet[i].active) {
      Sprites::drawSelfMasked(bullet[i].x - cameraOffset, bullet[i].y, bullet[i].sprite.sprite, bullet[i].sprite.frame);
    }
  }
}

void drawAmmo() {
  arduboy.setCursor(player.x+9 - cameraOffset, player.y);
  arduboy.print(MAX_BULLETS - bulletsUsed);
}
}
#include "bullet.h"

sprite_t muzzleFlashSprite = {
  ShootShoes::muzzleFlash,  //sprite
  0,                        //last frame
  muzzleFlashTransitions,   //frame transitions
  8,                        //dx
  0,                        //dy
  8,                        //w
  8,                        //h
};
animation_t muzzleFlash;

sprite_t bulletSprite = 
{
  ShootShoes::bullet, //sprite
  6,                  //last frame
  bulletTransitions,  //frame transitions
  0,                  //dx
  2,                  //dy
  4,                  //w
  4,                  //h
};
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
    Player::thrust();

    muzzleFlash.active = true;
    muzzleFlash.t = 0;
    muzzleFlash.frame = 0;

    bullet[chamber].animation.active = true;
    bullet[chamber].animation.x = player.animation.x;
    bullet[chamber].animation.y = player.animation.y;
    bullet[chamber].animation.frame = 0;
    bullet[chamber].animation.t = 0;
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
  muzzleFlash.frame = 0;
  muzzleFlash.t = 0;
  muzzleFlash.sprite = &muzzleFlashSprite;
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.animation.x - cameraOffset - muzzleFlash.sprite->dx, player.animation.y, muzzleFlash.sprite->sprite, muzzleFlash.frame);
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
  collisionCheck();

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].animation.active) {
      bullet[i].animation.x = int(1.0f*bullet[i].animation.x - bullet[i].v);
      bullet[i].v -= BULLET_ACCEL;
      bullet[i].animation.active = Utils::updateAnimation(&bullet[i].animation);
    }
  }
}

void collisionCheck() {
  for (int b = 0; b < MAX_BULLETS; b++) {
    window_t wd = Utils::getCollisionWindow(bullet[b].animation.x, bullet[b].animation.y);

    for (int i = wd.xMin; i <= wd.xMax; i++) {
      for (int j = wd.yMin; j <= wd.yMax; j++) {
        if (levelMap[i][j]) {
          if (levelMap[i][j] != DASH) {
            Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
            if (Utils::collides(bullet[b].animation, blockRect)) {
              bullet[b].animation.active = false;
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
    if (bullet[i].animation.active) {
      Sprites::drawSelfMasked(bullet[i].animation.x - cameraOffset, bullet[i].animation.y, bullet[i].animation.sprite->sprite, bullet[i].animation.frame);
    }
  }
}

void drawAmmo() {
  // arduboy.setCursor(player.animation.x + 9 - cameraOffset, player.animation.y);
  // arduboy.print(MAX_BULLETS - bulletsUsed);
}
}
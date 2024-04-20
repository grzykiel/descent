#include "bullet.h"

sprite_t muzzleFlashSprite;
animation_t muzzleFlash;

sprite_t bulletSprite;
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
    muzzleFlash.t = 0;
    muzzleFlash.frame = 0;

    /*bullet[chamber].active = true;
    bullet[chamber].x = player.x;
    bullet[chamber].y = player.y;
    bullet[chamber].sprite.frame = 0;
    bullet[chamber].sprite.t = 0;
    bullet[chamber].t = 0;
    bullet[chamber].v = BULLET_START_VEL;
    chamber = (chamber + 1) % MAX_BULLETS;*/

    bullet[chamber].animation.active = true;
    bullet[chamber].animation.x = player.x;
    bullet[chamber].animation.y = player.y;
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

  muzzleFlashSprite.sprite = ShootShoes::muzzleFlash;
  muzzleFlashSprite.last = 1; //TODO length function
  muzzleFlashSprite.transitions = muzzleFlashTransitions;
  muzzleFlashSprite.dx = 8;
  muzzleFlashSprite.dy = 0;
  muzzleFlashSprite.w = 8;
  muzzleFlashSprite.h = 8;

  muzzleFlash.active = false;
  muzzleFlash.frame = 0;
  muzzleFlash.t = 0;
  muzzleFlash.sprite = &muzzleFlashSprite;
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.x - cameraOffset - muzzleFlash.sprite->dx, player.y, muzzleFlash.sprite->sprite, muzzleFlash.frame);
    muzzleFlash.active = Game::updateAnimation(&muzzleFlash);
  }
}

void initBullets() {
  //init sprite
  bulletSprite.sprite = ShootShoes::bullet;
  bulletSprite.last = 8;
  bulletSprite.transitions = bulletTransitions;
  bulletSprite.dx = 0;
  bulletSprite.dy = 2;
  bulletSprite.w = 4;
  bulletSprite.h = 4;



  for (int i = 0; i < MAX_BULLETS; i++) {
    /*bullet[i].active = false;
    bullet[i].sprite.sprite = ShootShoes::bullet;
    bullet[i].sprite.transitions = bulletTransitions;
    bullet[i].sprite.last = BULLET_FRAME_LAST;*/
    bullet[i].animation.sprite = &bulletSprite;
    bullet[i].animation.active = false;
    bullet[i].animation.frame = 0;
    bullet[i].animation.t = 0;  
  }
}

void updateBullets() {
  collisionCheck();

  for (int i = 0; i < MAX_BULLETS; i++) {
    /*if (bullet[i].active) {
      bullet[i].x = int(1.0f * bullet[i].x - bullet[i].v);
      bullet[i].v -= BULLET_ACCEL;
      bullet[i].active = Game::updateSprite(&bullet[i].sprite);
    }*/
    if (bullet[i].animation.active) {
      bullet[i].animation.x = int(1.0f*bullet[i].animation.x - bullet[i].v);
      bullet[i].v -= BULLET_ACCEL;
      bullet[i].animation.active = Game::updateAnimation(&bullet[i].animation);
    }
  }
}

//TODO generic collision check
void collisionCheck() {
  for (int b = 0; b < MAX_BULLETS; b++) {
    window_t wd = Utils::getCollisionWindow(bullet[b].animation.x, bullet[b].animation.y);

    for (int i = wd.xMin; i <= wd.xMax; i++) {
      for (int j = wd.yMin; j <= wd.yMax; j++) {
        if (levelMap[i][j]) {
          if (levelMap[i][j] != DASH) {
            Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
            Rect bulletRect = Rect(bullet[b].animation.x, bullet[b].animation.y + 2, 4, 4);
            if (arduboy.collide(bulletRect, blockRect)) {
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
    /*if (bullet[i].active) {
      Sprites::drawSelfMasked(bullet[i].x - cameraOffset, bullet[i].y, bullet[i].sprite.sprite, bullet[i].sprite.frame);
    }*/
    if (bullet[i].animation.active) {
      Sprites::drawSelfMasked(bullet[i].animation.x - cameraOffset, bullet[i].animation.y, bullet[i].animation.sprite->sprite, bullet[i].animation.frame);
    }
  }
}

void drawAmmo() {
  arduboy.setCursor(player.x + 9 - cameraOffset, player.y);
  arduboy.print(MAX_BULLETS - bulletsUsed);
}
}
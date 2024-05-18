#include "enemies.h"

uint8_t blobTransitions[2] = { 45, 90 };

sprite_t blobSprite = {
  Enemies::blob,
  1,                // last frame
  blobTransitions,  // frame transitions
  0,                // dx
  2,                // dy
  5,                // w
  7,                // h
};

enemy_t enemy[1];
// enemy_t enemyBlob;


namespace Enemies {

void init() {
  uint8_t i = 0;
  enemy[i].animation.sprite = &blobSprite;
  enemy[i].animation.active = true;
  enemy[i].animation.frame = 0;
  enemy[i].animation.t = 0;
  enemy[i].animation.x = 272 * PIXEL_SCALE;
  enemy[i].animation.y = 32 * PIXEL_SCALE;

  enemy[i].vx = 0;
  enemy[i].vy = 0;
}

void update() {
  updatePositions();
  updateSprites();
}

void updatePositions() {
  uint8_t i = 0;
  int dx = player.animation.x - enemy[i].animation.x/PIXEL_SCALE;
  if (dx > 0) {
    enemy[i].vx = min(++enemy[i].vx, BLOB_MAX_VEL);
  } else if (dx < 0) {
    enemy[i].vx = max(--enemy[i].vx, -BLOB_MAX_VEL);
  }
  if (player.animation.y - enemy[i].animation.y / PIXEL_SCALE > 0) {
    enemy[i].vy = min(++enemy[i].vy, BLOB_MAX_VEL);
  } else if (player.animation.y - enemy[i].animation.y / PIXEL_SCALE < 0) {
    enemy[i].vy = max(--enemy[i].vy, -BLOB_MAX_VEL);
  }

  Utils::println(enemy[i].animation.x/PIXEL_SCALE);
  Utils::println(player.animation.x);
  Utils::println(dx);

  enemy[i].animation.x += enemy[i].vx;
  enemy[i].animation.y += enemy[i].vy;

  /*uint8_t maxVel = 8*4-1;
  if (x-jelly.x/128 > 0) {
    jelly.vx = min(jelly.vx+accel, maxVel);
  } else if (x-jelly.x/128 < 0) {
    jelly.vx = max(jelly.vx-accel, -maxVel);
  }
  jelly.x+=jelly.vx/4;

  if (y-jelly.y/128 > 0) {
    jelly.vy = min(jelly.vy+accel, maxVel);
  } else if (y-jelly.y/128 < 0) {
    jelly.vy = max(jelly.vy-accel, -maxVel);
  }
  jelly.y += jelly.vy/4;*/
}

void updateSprites() {
  uint8_t i = 0;
  if (!Utils::updateAnimation(&enemy[i].animation)) {
    enemy[i].animation.t = 0;
    enemy[i].animation.frame = 0;
  }
}

void draw() {
  uint8_t i = 0;
  Sprites::drawSelfMasked((enemy[i].animation.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.y / PIXEL_SCALE, enemy[i].animation.sprite->sprite, enemy[i].animation.frame);
}

}
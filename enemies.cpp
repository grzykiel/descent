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
  enemy[i].animation.pos.x = 272 * PIXEL_SCALE;
  enemy[i].animation.pos.y = 32 * PIXEL_SCALE;

  enemy[i].vx = 0;
  enemy[i].vy = 0;
}

void update() {
  for (uint8_t i=0; i<MAX_ENEMIES; i++) {
    position_t nextPos;
    velocity_t nextVel;
  }
  updatePositions();

  checkCollisions();
  
  updateSprites();
}

vector_t updatePositions(enemy_t enemy) {
  vector_t next;
  int dx = player.animation.pos.x - enemy.animation.pos.x;
  int dy = player.animation.pos.y - enemy.animation.pos.y;

  if (dx > 0) {

  }
}

//TODO remove
void updatePositions() {
  uint8_t i = 0;
  int dx = player.animation.pos.x - enemy[i].animation.pos.x/PIXEL_SCALE;
  if (dx > 0) {
    enemy[i].vx = min(++enemy[i].vx, BLOB_MAX_VEL);
  } else if (dx < 0) {
    enemy[i].vx = max(--enemy[i].vx, -BLOB_MAX_VEL);
  }
  if (player.animation.pos.y - enemy[i].animation.pos.y / PIXEL_SCALE > 0) {
    enemy[i].vy = min(++enemy[i].vy, BLOB_MAX_VEL);
  } else if (player.animation.pos.y - enemy[i].animation.pos.y / PIXEL_SCALE < 0) {
    enemy[i].vy = max(--enemy[i].vy, -BLOB_MAX_VEL);
  }

  enemy[i].animation.pos.x += enemy[i].vx;
  enemy[i].animation.pos.y += enemy[i].vy;

}

void checkCollisions() {

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
  Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->sprite, enemy[i].animation.frame);
}

}
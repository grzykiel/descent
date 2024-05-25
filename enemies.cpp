#include "enemies.h"
#include "bullet.h"


uint8_t blobTransitions[2] = { 45, 90 };

sprite_t blobSprite = {
  Enemies::blob,
  1,                // last frame
  blobTransitions,  // frame transitions
  1,                // dx
  0,                // dy
  7,                // w
  5,                // h
};

enemy_t enemy[MAX_ENEMIES];

namespace Enemies {

void init() {
  uint8_t i = 0;
  enemy[i].type = BLOB;
  enemy[i].animation.sprite = &blobSprite;
  enemy[i].animation.active = true;
  enemy[i].animation.frame = 0;
  enemy[i].animation.t = 0;
  enemy[i].animation.pos.x = 272 * PIXEL_SCALE;
  enemy[i].animation.pos.y = 32 * PIXEL_SCALE;

  enemy[i].animation.vel.x = 0;
  enemy[i].animation.vel.y = 0;
}

void update() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    position_t nextPos = enemy[i].animation.pos;
    velocity_t nextVel = enemy[i].animation.vel;
    updatePosition(enemy[i], &nextPos, &nextVel);
    checkCollisions(enemy[i], &nextPos, &nextVel);

    updateSprite(&enemy[i]);
    enemy[i].animation.pos = nextPos;
    checkBulletCollisions(enemy[i], &nextVel);
    enemy[i].animation.vel = nextVel;
  }
}

void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  // if enemy.type == BLOB
  int dx = player.animation.pos.x / PIXEL_SCALE - enemy.animation.pos.x / PIXEL_SCALE;
  if (dx > 0) {
    nextVel->x = min(++enemy.animation.vel.x, BLOB_MAX_VEL);
  } else if (dx < 0) {
    nextVel->x = max(--enemy.animation.vel.x, -BLOB_MAX_VEL);
  }

  int dy = player.animation.pos.y / PIXEL_SCALE - enemy.animation.pos.y / PIXEL_SCALE;
  if (dy > 0) {
    nextVel->y = min(++enemy.animation.vel.y, BLOB_MAX_VEL);
  } else if (dy < 0) {
    nextVel->y = max(--enemy.animation.vel.y, -BLOB_MAX_VEL);
  }

  nextPos->x += nextVel->x;
  nextPos->y += nextVel->y;
}


void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {

  window_t wd = Utils::getCollisionWindow(enemy.animation.pos);
  // tile collisions
  for (uint8_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j] && levelMap[i][j] != DASH) {
        Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE);
        collision_t temp = Utils::collisionCorrect(enemy.animation, nextPos, block);
        // set velocity according to collision
        if (temp.v) nextVel->x = 0;
        if (temp.h) nextVel->y = 0;
      }
    }
  }
}

void checkBulletCollisions(enemy_t enemy, velocity_t *nextVel) {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].animation.active) {
      if (Utils::collides(enemy.animation, bullet[i].animation)) {
        if (enemy.type == BLOB) {
          nextVel->x = BLOB_RECOIL_VEL;
        }
      }
    }
  }
}

void updateSprite(enemy_t *enemy) {
  if (!Utils::updateAnimation(&enemy->animation)) {
    enemy->animation.t = 0;
    enemy->animation.frame = 0;
  }
}


void draw() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (enemy[i].animation.active) {
      Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->sprite, enemy[i].animation.frame);
    }
  }
}

}
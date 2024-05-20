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

namespace Enemies {

void init() {
  uint8_t i = 0;
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
  for (uint8_t i=0; i<MAX_ENEMIES; i++) {
    position_t nextPos = enemy[i].animation.pos;
    velocity_t nextVel = enemy[i].animation.vel;
    updatePosition(enemy[i], &nextPos, &nextVel);
    checkCollisions(enemy[i], &nextPos, &nextVel);

    updateSprite(enemy[i]); //TODO update
    enemy[i].animation.pos = nextPos;
    enemy[i].animation.vel = nextVel;
  }

}

void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  // if enemy.type == BLOB
  int dx = player.animation.pos.x - enemy.animation.pos.x/PIXEL_SCALE;
  if (dx > 0) {
    nextVel->x = min(++enemy.animation.vel.x, BLOB_MAX_VEL);
  } else if (dx < 0) {
    nextVel->x = max(--enemy.animation.vel.x, -BLOB_MAX_VEL);
  }

  int dy = player.animation.pos.y - enemy.animation.pos.y / PIXEL_SCALE;
  if (dy > 0) {
    nextVel->y = min(++enemy.animation.vel.y, BLOB_MAX_VEL);
  } else if (dy < 0) {
    nextVel->y = max(--enemy.animation.vel.y, -BLOB_MAX_VEL);
  }

  nextPos->x += nextVel->x;
  nextPos->y += nextVel->y;
}

//TODO
//- fix pixel scaling
//- no collision with DASH
void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  position_t posPix;
  posPix.x = nextPos->x/PIXEL_SCALE;
  posPix.y = nextPos->y/PIXEL_SCALE;
  window_t wd = Utils::getCollisionWindow(posPix);
  // tile collisions
  for (int i = wd.xMin; i <= wd.xMax; i++) {
    for (int j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = levelMap[i][j] == DASH ? Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE) : Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        collision_t temp = Utils::collisionCorrect(enemy.animation, &posPix, block);
        nextPos->x = posPix.x*PIXEL_SCALE;
        nextPos->y = posPix.y*PIXEL_SCALE;
        // set velocity according to collision
        if (temp.v) nextVel->x = 0;
        if (temp.h) nextVel->y = 0;
      }
    }
  }
}

void updateSprite(enemy_t enemy) {
  if (!Utils::updateAnimation(&enemy.animation)) {
    enemy.animation.t = 0;
    enemy.animation.frame = 0;
  }
}


void draw() {
  uint8_t i = 0;
  // Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->sprite, enemy[i].animation.frame);
}

}
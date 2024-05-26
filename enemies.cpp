#include "enemies.h"
#include "bullet.h"


uint8_t blobTransitions[2] = { 45, 90 };
uint8_t batTransition[2] = { 30, 60 };

sprite_t blobSprite = {
  Enemies::blob,
  nullptr,
  1,                // last frame
  blobTransitions,  // frame transitions
  1,                // dx
  0,                // dy
  7,                // w
  5,                // h
};

sprite_t batHangingSprite = {
  Enemies::batHanging,
  nullptr,
  0,
  nullptr,
  4,
  2,
  4,
  4,
};

enemy_t enemy[MAX_ENEMIES];

uint8_t currentEnemy = 0;

namespace Enemies {

void init() {
}

void update() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (enemy[i].animation.active) {
      // Utils::println(i);
      position_t nextPos = enemy[i].animation.pos;
      velocity_t nextVel = enemy[i].animation.vel;
      updatePosition(enemy[i], &nextPos, &nextVel);
      checkCollisions(enemy[i], &nextPos, &nextVel);

      updateSprite(&enemy[i]);
      enemy[i].animation.pos = nextPos;
      checkBulletCollisions(&enemy[i], &nextVel);
      enemy[i].animation.vel = nextVel;
    }
  }
}

void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  if (enemy.type == EnemyType::blob) {
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
  }

  nextPos->x += nextVel->x;
  nextPos->y += nextVel->y;
}


void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  if (enemy.type == EnemyType::blob) {
    window_t wd = Utils::getCollisionWindow(enemy.animation.pos);
    // tile collisions
    for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
      for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
        if (levelMap[i][j] && levelMap[i][j] != DASH) {
          Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
          collision_t temp = Utils::collisionCorrect(enemy.animation, nextPos, block);
          // set velocity according to collision
          if (temp.v) nextVel->x = 0;
          if (temp.h) nextVel->y = 0;
        }
      }
    }
  }
}

void checkBulletCollisions(enemy_t *enemy, velocity_t *nextVel) {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].animation.active) {
      if (Utils::collides(enemy->animation, bullet[i].animation)) {
        bullet[i].animation.active = false;
        enemy->hp--;
        if (enemy->hp < 1) {
          enemy->animation.active = false;
        } else if (enemy->type == EnemyType::blob) {
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
      if (enemy[i].animation.dir == Direction::left) {
        Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->spriteL, enemy[i].animation.frame);
      } else {
        Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->spriteR, enemy[i].animation.frame);
      }
      // arduboy.setCursor(enemy[i].animation.pos.x / PIXEL_SCALE - cameraOffset, enemy[i].animation.pos.y/PIXEL_SCALE);
      // arduboy.print(enemy[i].hp);
    }
  }
}

void spawn(EnemyType type, uint16_t x, uint8_t y) {
  if (type == EnemyType::blob) {
    enemy[currentEnemy].animation.sprite = &blobSprite;
    enemy[currentEnemy].animation.dir = Direction::right;
    enemy[currentEnemy].hp = BLOB_HP;
  } else if (type == EnemyType::hangingBat) {
    enemy[currentEnemy].animation.sprite = &batHangingSprite;
    enemy[currentEnemy].hp = BAT_HP;
  }
  enemy[currentEnemy].animation.active = true;
  enemy[currentEnemy].type = type;
  enemy[currentEnemy].animation.frame = 0;
  enemy[currentEnemy].animation.t = 0;
  enemy[currentEnemy].animation.pos.x = x * PIXEL_SCALE;
  enemy[currentEnemy].animation.pos.y = y * PIXEL_SCALE;
  enemy[currentEnemy].animation.vel.x = 0;
  enemy[currentEnemy].animation.vel.y = 0;

  currentEnemy = (currentEnemy + 1) % MAX_ENEMIES;
}



}
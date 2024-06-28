#include "enemies.h"

uint8_t blobTransitions[2] = { 45, 90 };
uint8_t batTransitions[2] = { 15, 30 };
uint8_t wormTransitions[2] = { 15, 30 };  //{ 45, 90 };
uint8_t tortoiseTransitions[2] = { 60, 120 };

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
  3,
  1,
  5,
  5,
};

sprite_t batSprite = {
  Enemies::batRight,
  Enemies::batLeft,
  1,
  batTransitions,
  2,
  1,
  6,
  4
};

sprite_t wormSprite = {
  Enemies::wormRight,
  Enemies::wormLeft,
  1,
  wormTransitions,
  0,
  0,
  4,
  3
};

sprite_t crawlerSprite = {
  Enemies::crawler,
  nullptr,
  0,
  nullptr,
  0,
  0,
  7,
  4
};

sprite_t tortoiseSprite = {
  Enemies::tortoiseRight,
  Enemies::tortoiseLeft,
  1,
  tortoiseTransitions,
  0,
  1,
  6,
  3
};

enemy_t enemy[MAX_ENEMIES];

uint8_t currentEnemy = 0;

namespace Enemies {

void init() {
}


void update() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (!enemy[i].animation.active) continue;

    if (enemy[i].type == EnemyType::hangingBat) {
      if (abs(player.animation.pos.x - enemy[i].animation.pos.x) / PIXEL_SCALE < 4) {
        wake(&enemy[i]);
      }
      uint8_t x = ((enemy[i].animation.pos.x / PIXEL_SCALE) / 8) + 1;
      uint8_t y = (enemy[i].animation.pos.y / PIXEL_SCALE) / 8;
      if (!levelMap[MAPHEIGHT - x - 1][y]) wake(&enemy[i]);
      continue;
    }

    position_t nextPos = enemy[i].animation.pos;
    velocity_t nextVel = enemy[i].animation.vel;

    // movement update
    if (enemy[i].type == EnemyType::worm || enemy[i].type == EnemyType::tortoise) {
      updateCrawling(&enemy[i], &nextPos, &nextVel);
    } else if (enemy[i].type == EnemyType::blob || enemy[i].type == EnemyType::bat) {
      updateFlying(&enemy[i], &nextPos, &nextVel);
    }
    nextPos.x += nextVel.x;
    nextPos.y += nextVel.y;

    checkTileCollision(&enemy[i], &nextPos, &nextVel);

    enemy[i].animation.pos = nextPos;
    checkBulletCollisions(&enemy[i], &nextVel);
    enemy[i].animation.vel = nextVel;
  }
}

void updateCrawling(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  nextVel->x = max(nextVel->x + GRAVITY, -4 * PIXEL_SCALE);

  if (!updateSprite(enemy)) {
    nextVel->y = 0;
    return;
  }

  int8_t vel = enemy->type == EnemyType::worm ? 1 : 2;
  if (enemy->animation.dir == Direction::right) {
    if (nextPos->y / PIXEL_SCALE > SCREENRIGHT - enemy->animation.sprite->dy - enemy->animation.sprite->w - 2) {
      enemy->animation.dir = Direction::left;
    } else {
      nextVel->y = vel * PIXEL_SCALE;
    }
  } else if (enemy->animation.dir == Direction::left) {
    if (nextPos->y / PIXEL_SCALE < SCREENLEFT + 2) {
      enemy->animation.dir = Direction::right;
    } else {
      nextVel->y = -vel * PIXEL_SCALE;
    }
  }
}

void updateFlying(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  int dx = player.animation.pos.x / PIXEL_SCALE - enemy->animation.pos.x / PIXEL_SCALE;
  int dy = player.animation.pos.y / PIXEL_SCALE - enemy->animation.pos.y / PIXEL_SCALE;
  if (enemy->type == EnemyType::blob) {
    if (dx > 0) {
      nextVel->x = min(++enemy->animation.vel.x, BLOB_MAX_VEL);
    } else if (dx < 0) {
      nextVel->x = max(--enemy->animation.vel.x, -BLOB_MAX_VEL);
    }

    if (dy > 0) {
      nextVel->y = min(++enemy->animation.vel.y, BLOB_MAX_VEL);
    } else if (dy < 0) {
      nextVel->y = max(--enemy->animation.vel.y, -BLOB_MAX_VEL);
    }
  } else if (enemy->type == EnemyType::bat) {
    nextVel->x = Utils::sign(dx) * BAT_VEL;
    nextVel->y = Utils::sign(dy) * BAT_VEL;

    enemy->animation.dir = (nextVel->y > 0) ? Direction::right : Direction::left;
  }

  updateSprite(enemy);
}

void checkTileCollision(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  window_t wd = Utils::getCollisionWindow(enemy->animation.pos);

  for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        if (levelMap[i][j] == DASH) {
          if (enemy->type == EnemyType::blob) {
            continue;
          } else {
            block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE);
          }
        }
        collision_t temp = Utils::collisionCorrect(enemy->animation, nextPos, block);

        if (temp.v == BOTTOM || temp.v == TOP) {
          nextVel->x = 0;
        } 
        if (temp.h == LEFT || temp.h == RIGHT) {
          nextVel->y = 0;
          if (enemy->type == EnemyType::worm || enemy->type == EnemyType::tortoise) {
            if (temp.h == LEFT) {
              enemy->animation.dir = Direction::right;
            } else if (temp.h == RIGHT) {
              enemy->animation.dir = Direction::left;
            }
          }
        } else {
          if ((enemy->type == EnemyType::worm || enemy->type == EnemyType::tortoise) && ledgeDetect(enemy->animation)) {
            enemy->animation.dir = enemy->animation.dir == Direction::left ? Direction::right : Direction::left;
          }
        }
      }
    }
  }
}

bool ledgeDetect(animation_t animation) {
  uint16_t x = animation.pos.x / PIXEL_SCALE / BLOCKSIZE;
  uint8_t y;
  if (animation.dir == Direction::left) {
    y = animation.pos.y / PIXEL_SCALE / 8;
  } else {
    y = (animation.pos.y / PIXEL_SCALE + animation.sprite->dy + animation.sprite->w) / 8;
  }

  // arduboy.drawRect(x * BLOCKSIZE - cameraOffset, y * BLOCKSIZE, 8, 8);
  // arduboy.drawRect((x-1) * BLOCKSIZE - cameraOffset, y * BLOCKSIZE, 8, 8);

  return (!levelMap[MAPHEIGHT - x- 1][y] && !levelMap[MAPHEIGHT - x][y]);
}

void checkBulletCollisions(enemy_t *enemy, velocity_t *nextVel) {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i].active) {
      if (Utils::collides(enemy->animation, bullet[i])) {
        bullet[i].active = false;
        if (enemy->type == EnemyType::tortoise) {
          Particles::spawnClink(enemy->animation.pos, 4, 2);
          return;
        }
        enemy->hp--;
        enemy->animation.iframe = 30;
        if (enemy->hp < 1) {
          kill(enemy, true);
        } else if (enemy->type == EnemyType::blob) {
          nextVel->x = BLOB_RECOIL_VEL;
        }
      }
    }
  }
}

void kill(enemy_t *enemy, bool shot) {
  enemy->animation.active = false;
  if (shot) {
    Particles::spawnExplosion(enemy->animation.pos,
                              enemy->animation.sprite->dx + enemy->animation.sprite->h / 2,
                              enemy->animation.sprite->dy + enemy->animation.sprite->w / 2);
  } else {
    Particles::spawnPop(enemy->animation.pos,
                        enemy->animation.sprite->dx + enemy->animation.sprite->h / 2,
                        enemy->animation.sprite->dy + enemy->animation.sprite->w / 2);
  }
}

bool updateSprite(enemy_t *enemy) {
  if (enemy->type == EnemyType::hangingBat) return;
  if (!Utils::updateAnimation(&enemy->animation)) {
    enemy->animation.t = 0;
    enemy->animation.frame = 0;
    return true;
  }
  return false;
}


void draw() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (enemy[i].animation.active & !Utils::flickering(&enemy[i].animation)) {
      if (enemy[i].animation.dir == Direction::left) {
        Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->spriteL, enemy[i].animation.frame);
      } else {
        Sprites::drawSelfMasked((enemy[i].animation.pos.x / PIXEL_SCALE) - cameraOffset, enemy[i].animation.pos.y / PIXEL_SCALE, enemy[i].animation.sprite->spriteR, enemy[i].animation.frame);
      }
    }
  }
}

void spawn(EnemyType type, uint16_t x, uint8_t y) {
  if (type == EnemyType::blob) {
    enemy[currentEnemy].animation.sprite = &blobSprite;
    enemy[currentEnemy].hp = BLOB_HP;
  } else if (type == EnemyType::hangingBat) {
    enemy[currentEnemy].animation.sprite = &batHangingSprite;
    enemy[currentEnemy].hp = BAT_HP;
  } else if (type == EnemyType::worm) {
    enemy[currentEnemy].animation.sprite = &wormSprite;
    enemy[currentEnemy].hp = WORM_HP;
  } else if (type == EnemyType::tortoise) {
    enemy[currentEnemy].animation.sprite = &tortoiseSprite;
    enemy[currentEnemy].hp = TORTOISE_HP;
  } else if (type == EnemyType::crawler) {
    enemy[currentEnemy].animation.sprite = &crawlerSprite;
    enemy[currentEnemy].hp = CRAWLER_HP;
  }
  enemy[currentEnemy].animation.dir = Direction::right;
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

void wake(enemy_t *bat) {
  if (!(bat->type == EnemyType::hangingBat)) return;

  bat->type = EnemyType::bat;
  bat->animation.sprite = &batSprite;
}


void onShiftMap() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (!enemy[i].animation.active) continue;
    if (enemy[i].animation.pos.x < 49152 - 128 * PIXEL_SCALE) {  //TODO #define threshold
      Level::shiftPos(&enemy[i].animation.pos);
    } else {
      enemy[i].animation.active = false;
    }
  }
}
}
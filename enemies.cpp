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
  Enemies::crawler,
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
      uint8_t x = ((enemy[i].animation.pos.x / PIXEL_SCALE) / BLOCKSIZE) + 1;
      uint8_t y = (enemy[i].animation.pos.y / PIXEL_SCALE) / BLOCKSIZE;
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
    } else if (enemy[i].type == EnemyType::crawler) {
      updateCrawler(&enemy[i], &nextPos, &nextVel);
    }

    nextPos.x += nextVel.x;
    nextPos.y += nextVel.y;

    if (enemy[i].type == EnemyType::crawler) {
      checkCrawlerCollision(&enemy[i], &nextPos, &nextVel);
    } else {
      checkTileCollision(&enemy[i], &nextPos, &nextVel);
    }

    enemy[i].animation.pos = nextPos;
    checkBulletCollisions(&enemy[i], &nextVel);
    enemy[i].animation.vel = nextVel;
  }
}

void updateCrawler(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  if (enemy->animation.dir == Direction::left) {
    nextVel->x = 0;
    nextVel->y = -CRAWLER_VEL;
  } else if (enemy->animation.dir == Direction::right) {
    nextVel->x = 0;
    nextVel->y = CRAWLER_VEL;
  } else if (enemy->animation.dir == Direction::up) {
    nextVel->x = CRAWLER_VEL;
    nextVel->y = 0;
  } else if (enemy->animation.dir == Direction::down) {
    nextVel->x = -CRAWLER_VEL;
    nextVel->y = 0;
  }
}

void checkCrawlerCollision(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  // arduboy.drawRect(enemy->animation.pos.x/PIXEL_SCALE + enemy->animation.sprite->dx - cameraOffset, enemy->animation.pos.y/PIXEL_SCALE + enemy->animation.sprite->dy, enemy->animation.sprite->h, enemy->animation.sprite->w);
  uint16_t x;
  uint16_t x_m;
  uint8_t y;
  if (enemy->animation.dir == Direction::left) {
    x = nextPos->x / PIXEL_SCALE / BLOCKSIZE;
    x_m = (MAPHEIGHT - x - 1);
    y = (nextPos->y / PIXEL_SCALE + enemy->animation.sprite->dy) / BLOCKSIZE;

    if (levelMap[x_m][y]) {
      setCrawlerDirection(enemy, Direction::up);
      nextPos->x = x * PIXEL_SCALE * BLOCKSIZE;
      nextPos->y = (y + 1) * PIXEL_SCALE * BLOCKSIZE;
      nextVel->y = 0;
    } else if (!levelMap[x_m + 1][y]) {
      if (levelMap[x_m + 1][y + 1]) {
        setCrawlerDirection(enemy, Direction::down);
        nextPos->x = (x - 1) * PIXEL_SCALE * BLOCKSIZE;
        nextPos->y = y * PIXEL_SCALE * BLOCKSIZE;
        // nextVel->y = 0;
      } else {
        //crawlerDrop(enemy);
      }
    }
  } else if (enemy->animation.dir == Direction::up) {
    x = (nextPos->x / PIXEL_SCALE + enemy->animation.sprite->h) / BLOCKSIZE;
    x_m = (MAPHEIGHT - x - 1);
    y = nextPos->y / PIXEL_SCALE / BLOCKSIZE;
    if (levelMap[x_m][y]) {
      setCrawlerDirection(enemy, Direction::right);
      nextPos->x = (x - 1) * PIXEL_SCALE * BLOCKSIZE;
      nextPos->y = y * PIXEL_SCALE * BLOCKSIZE;
    } else if (!levelMap[x_m][y - 1]) {
      if (levelMap[x_m + 1][y - 1]) {
        setCrawlerDirection(enemy, Direction::left);
        nextPos->x = x * PIXEL_SCALE * BLOCKSIZE;
        nextPos->y = (y - 1) * PIXEL_SCALE * BLOCKSIZE;
      } else {
        //crawlerDrop(enemy);
      }
    }
  } else if (enemy->animation.dir == Direction::right) {
    x = (nextPos->x / PIXEL_SCALE + enemy->animation.sprite->dx + enemy->animation.sprite->h) / BLOCKSIZE;
    x_m = (MAPHEIGHT - x - 1);
    y = (nextPos->y / PIXEL_SCALE + enemy->animation.sprite->w) / BLOCKSIZE;

    if (levelMap[x_m][y]) {
      setCrawlerDirection(enemy, Direction::down);
      nextPos->x = x * PIXEL_SCALE * BLOCKSIZE;
      nextPos->y = (y - 1) * PIXEL_SCALE * BLOCKSIZE;
    } else if (!levelMap[x_m - 1][y]) {
      if (levelMap[x_m - 1][y - 1]) {
        setCrawlerDirection(enemy, Direction::up);
        nextPos->x = (x + 1) * PIXEL_SCALE * BLOCKSIZE;
        nextPos->y = y * PIXEL_SCALE * BLOCKSIZE;
      } else {
        //crawlerDrop();
      }
    }
  } else if (enemy->animation.dir == Direction::down) {
    x = (nextPos->x / PIXEL_SCALE + enemy->animation.sprite->dx) / BLOCKSIZE;
    x_m = (MAPHEIGHT - x - 1);
    y = (nextPos->y / PIXEL_SCALE + enemy->animation.sprite->dy + enemy->animation.sprite->w) / BLOCKSIZE;
    // arduboy.drawRect(x * BLOCKSIZE - cameraOffset, y * BLOCKSIZE, 8, 8);

    if (levelMap[x_m][y]) {
      setCrawlerDirection(enemy, Direction::left);
      nextPos->x = (x + 1) * PIXEL_SCALE * BLOCKSIZE;
      nextPos->y = y * PIXEL_SCALE * BLOCKSIZE;
    } else if (!levelMap[x_m][y + 1]) {
      if (levelMap[x_m - 1][y + 1]) {
        setCrawlerDirection(enemy, Direction::right);
        nextPos->x = x * PIXEL_SCALE * BLOCKSIZE;
        nextPos->y = (y + 1) * PIXEL_SCALE * BLOCKSIZE;
      }
    } else {
      //crawlerDrop()
    }
  }
}

void updateCrawling(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  nextVel->x = max(nextVel->x + GRAVITY, -4 * PIXEL_SCALE);  //TODO redefine terminal velocity

  if (!updateSprite(enemy)) {
    nextVel->y = 0;
    return;
  }

  int8_t vel = enemy->type == EnemyType::worm ? WORM_VEL : TORTOISE_VEL;
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
          /*if (enemy->type == EnemyType::crawler) {
            if (temp.v == TOP && enemy->animation.frame == CRAWLER_RIGHT) {
              setCrawlerDirection(enemy, Direction::right);
            } else if (temp.v == BOTTOM && enemy->animation.frame == CRAWLER_LEFT) {
              setCrawlerDirection(enemy, Direction::left);
            }
          }*/
        }
        if (temp.h == LEFT || temp.h == RIGHT) {
          nextVel->y = 0;
          if (enemy->type == EnemyType::worm || enemy->type == EnemyType::tortoise) {
            if (temp.h == LEFT) {
              enemy->animation.dir = Direction::right;
            } else if (temp.h == RIGHT) {
              enemy->animation.dir = Direction::left;
            }
          } /*else if (enemy->type == EnemyType::crawler) {
            if (temp.h == LEFT && enemy->animation.frame == CRAWLER_UP) {
              setCrawlerDirection(enemy, Direction::up);
            } else if (temp.h == RIGHT && enemy->animation.frame == CRAWLER_DOWN) {
              setCrawlerDirection(enemy, Direction::down);
            }
          }*/
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
    y = animation.pos.y / PIXEL_SCALE / BLOCKSIZE;
  } else {
    y = (animation.pos.y / PIXEL_SCALE + animation.sprite->dy + animation.sprite->w) / 8;
  }

  // arduboy.drawRect(x * BLOCKSIZE - cameraOffset, y * BLOCKSIZE, 8, 8);
  // arduboy.drawRect((x-1) * BLOCKSIZE - cameraOffset, y * BLOCKSIZE, 8, 8);

  return (!levelMap[MAPHEIGHT - x - 1][y] && !levelMap[MAPHEIGHT - x][y]);
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
  enemy[currentEnemy].animation.dir = random(0, 2) ? Direction::right : Direction::left;
  enemy[currentEnemy].animation.active = true;
  enemy[currentEnemy].type = type;
  enemy[currentEnemy].animation.frame = 0;
  enemy[currentEnemy].animation.t = 0;
  enemy[currentEnemy].animation.pos.x = x * PIXEL_SCALE;
  enemy[currentEnemy].animation.pos.y = y * PIXEL_SCALE;
  enemy[currentEnemy].animation.vel.x = 0;
  enemy[currentEnemy].animation.vel.y = 0;

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
    enemy[currentEnemy].animation.dir = Direction::left;
  }

  currentEnemy = (currentEnemy + 1) % MAX_ENEMIES;
}

void wake(enemy_t *bat) {
  if (!(bat->type == EnemyType::hangingBat)) return;

  bat->type = EnemyType::bat;
  bat->animation.sprite = &batSprite;
}

void setCrawlerDirection(enemy_t *crawler, Direction dir) {
  crawler->animation.dir = dir;
  if (dir == Direction::left) {
    crawler->animation.frame = CRAWLER_UP;
    crawler->animation.sprite->dx = 0;
    crawler->animation.sprite->dy = 1;
    crawler->animation.sprite->w = CRAWLER_WIDTH;
    crawler->animation.sprite->h = CRAWLER_HEIGHT;
  } else if (dir == Direction::right) {
    crawler->animation.frame = CRAWLER_DOWN;
    crawler->animation.sprite->dx = 3;
    crawler->animation.sprite->dy = 0;
    crawler->animation.sprite->w = CRAWLER_WIDTH;
    crawler->animation.sprite->h = CRAWLER_HEIGHT;
  } else if (dir == Direction::up) {
    crawler->animation.frame = CRAWLER_RIGHT;
    crawler->animation.sprite->dx = 0;
    crawler->animation.sprite->dy = 1;
    crawler->animation.sprite->w = CRAWLER_HEIGHT;
    crawler->animation.sprite->h = CRAWLER_WIDTH;
  } else if (dir == Direction::down) {
    crawler->animation.frame = CRAWLER_LEFT;
    crawler->animation.sprite->dx = 0;
    crawler->animation.sprite->dy = 3;
    crawler->animation.sprite->w = CRAWLER_HEIGHT;
    crawler->animation.sprite->h = CRAWLER_WIDTH;
  }
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
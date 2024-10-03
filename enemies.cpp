#include "enemies.h"

const uint8_t blobTransitions[2] PROGMEM = { 45, 90 };
const uint8_t batTransitions[2] PROGMEM = { 15, 30 };
const uint8_t wormTransitions[2] PROGMEM = { 15, 30 };  //{ 45, 90 };
const uint8_t tortoiseTransitions[2] PROGMEM = { 60, 120 };

sprite_t blobSprite = {
  Enemies::blob,
  Enemies::blob,
  1,                // last frame
  blobTransitions,  // frame transitions
  1,                // dx
  0,                // dy
  7,                // w
  5,                // h
};

sprite_t batHangingSprite = {
  Enemies::batHanging,
  Enemies::batHanging,
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

//TODO remove
/*
sprite_t crawlerSprite = {
  Enemies::crawler,
  Enemies::crawler,
  0,
  nullptr,
  0,
  2,
  CRAWLER_WIDTH,
  CRAWLER_HEIGHT
};
*/

sprite_t crawlerSpriteUp = {
  Enemies::crawler,
  Enemies::crawler,
  0,
  nullptr,
  0,
  2,
  CRAWLER_WIDTH,
  CRAWLER_HEIGHT
};

sprite_t crawlerSpriteDown = {
  Enemies::crawler,
  Enemies::crawler,
  0,
  nullptr,
  4,
  1,
  CRAWLER_WIDTH,
  CRAWLER_HEIGHT
};

sprite_t crawlerSpriteLeft = {
  Enemies::crawler,
  Enemies::crawler,
  0,
  nullptr,
  2,
  4,
  CRAWLER_HEIGHT,
  CRAWLER_WIDTH
};

sprite_t crawlerSpriteRight = {
  Enemies::crawler,
  Enemies::crawler,
  0,
  nullptr,
  1,
  0,
  CRAWLER_HEIGHT,
  CRAWLER_WIDTH
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
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    enemy[i].animation.active = false;
  }
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
    } else if (enemy[i].type == EnemyType::crawler || enemy[i].type == EnemyType::fallingCrawler) {
      updateCrawler(&enemy[i], &nextPos, &nextVel);
    }

    nextPos.x += nextVel.x;
    nextPos.y += nextVel.y;

    if (enemy[i].type == EnemyType::crawler || enemy[i].type == EnemyType::fallingCrawler) {
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
  if (enemy->type == EnemyType::fallingCrawler) {
    nextVel->x = max(nextVel->x + GRAVITY, TERMINAL_VELOCITY * PIXEL_SCALE);
    return;
  }

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

void updateCrawling(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  nextVel->x = max(nextVel->x + GRAVITY, TERMINAL_VELOCITY * PIXEL_SCALE);

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
      if (!levelMap[i][j]) continue;

      Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
      if (levelMap[i][j] == DASH) {
        if (enemy->type == EnemyType::blob) {
          continue;
        } else {
          block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + DASH_OFFSET, j * BLOCKSIZE, DASH_HEIGHT, BLOCKSIZE);
        }
      }
      collision_t temp = Utils::collisionCorrect(enemy->animation, nextPos, block);

      // arduboy.drawRect(nextPos->x / PIXEL_SCALE + enemy->animation.sprite->dx - cameraOffset, nextPos->y / PIXEL_SCALE + enemy->animation.sprite->dy, enemy->animation.sprite->h, enemy->animation.sprite->w);

      if (enemy->type == EnemyType::bat || enemy->type == EnemyType::blob) {
        if (temp.v) {
          nextVel->x = 0;
        }
        if (temp.h) {
          nextVel->y = 0;
        }
      } else if (enemy->type == EnemyType::worm || enemy->type == EnemyType::tortoise) {
        if (temp.v) {
          nextVel->x = 0;
        }
        if (temp.h == LEFT) {
          enemy->animation.dir = Direction::right;
          nextVel->y = 0;
        } else if (temp.h == RIGHT) {
          enemy->animation.dir = Direction::left;
          nextVel->y = 0;
        } else if (ledgeDetect(enemy->animation)) {
          enemy->animation.dir = enemy->animation.dir == Direction::left ? Direction::right : Direction::left;
        }
      }
    }
  }
}

void checkCrawlerCollision(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel) {
  window_t wd = Utils::getCollisionWindow(enemy->animation.pos);
  bool rotationCollision = false;
  bool grip = false;

  for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (!levelMap[i][j]) {
        if (enemy->type == EnemyType::crawler) {
          if ((enemy->animation.frame == CRAWLER_RIGHT && enemy->animation.pos.y / PIXEL_SCALE <= SCREENLEFT + 1)
              || (enemy->animation.frame == CRAWLER_LEFT && enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy + CRAWLER_HEIGHT >= SCREENRIGHT - 1)) {
            rotationCollision = true;
            grip = true;
          }
        }
        continue;
      }

      Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
      if (levelMap[i][j] == DASH) {
        block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + DASH_OFFSET, j * BLOCKSIZE, DASH_HEIGHT, BLOCKSIZE);
      }
      collision_t temp = Utils::collisionCorrect(enemy->animation, nextPos, block);

      // arduboy.drawRect(nextPos->x / PIXEL_SCALE + enemy->animation.sprite->dx - cameraOffset, nextPos->y / PIXEL_SCALE + enemy->animation.sprite->dy, enemy->animation.sprite->h, enemy->animation.sprite->w);

      if (enemy->type == EnemyType::fallingCrawler) {
        if (temp.v == BOTTOM) {
          nextVel->x = 0;
          uint16_t x = (nextPos->x / PIXEL_SCALE + enemy->animation.sprite->dx) / BLOCKSIZE;
          nextPos->x = x * BLOCKSIZE * PIXEL_SCALE;
          uint16_t y = (nextPos->y / PIXEL_SCALE + enemy->animation.sprite->dy) / BLOCKSIZE;
          nextPos->y = y * BLOCKSIZE * PIXEL_SCALE;
          crawlerLand(enemy, nextVel);
          return;
        }
        continue;
      } else if (enemy->type == EnemyType::crawler) {
        if (enemy->animation.frame == CRAWLER_UP) {
          if (temp.h == LEFT || nextPos->y / PIXEL_SCALE < SCREENLEFT) {
            setCrawlerDirection(enemy, Direction::up);
            nextVel->y = 0;
            nextPos->y = (nextPos->y / PIXEL_SCALE + 2) * PIXEL_SCALE;  //+= 2 * PIXEL_SCALE;
            return;
          } else {
            Rect r = Rect(nextPos->x / PIXEL_SCALE - 5, nextPos->y / PIXEL_SCALE, CRAWLER_WIDTH, CRAWLER_HEIGHT);
            rotationCollision = rotationCollision || arduboy.collide(r, block);

            r = Rect(enemy->animation.pos.x / PIXEL_SCALE - 1, enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy, 1, CRAWLER_WIDTH);
            // arduboy.drawRect(r.x - cameraOffset, r.y, r.width, r.height);
            grip = grip || arduboy.collide(r, block);
          }
        } else if (enemy->animation.frame == CRAWLER_DOWN) {
          if (temp.h == RIGHT || ((nextPos->y / PIXEL_SCALE) + 8 > SCREENRIGHT)) {
            setCrawlerDirection(enemy, Direction::down);
            nextVel->y = 0;
            nextPos->x = (nextPos->x / PIXEL_SCALE + 1) * PIXEL_SCALE;  //+= 1 * PIXEL_SCALE;
            nextPos->y = (nextPos->y / PIXEL_SCALE - 2) * PIXEL_SCALE;  //-= 2 * PIXEL_SCALE;
            return;
          } else {
            Rect r = Rect(nextPos->x / PIXEL_SCALE + 7, nextPos->y / PIXEL_SCALE + 4, CRAWLER_WIDTH, CRAWLER_HEIGHT);
            rotationCollision = rotationCollision || arduboy.collide(r, block);

            r = Rect(enemy->animation.pos.x / PIXEL_SCALE + enemy->animation.sprite->dx + CRAWLER_HEIGHT, enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy, 1, CRAWLER_WIDTH);
            grip = grip || arduboy.collide(r, block);
            // arduboy.drawRect(r.x - cameraOffset, r.y, r.width, r.height);
          }
        } else if (enemy->animation.frame == CRAWLER_RIGHT) {
          if (temp.v == TOP) {
            setCrawlerDirection(enemy, Direction::right);
            nextVel->x = 0;
            nextPos->x = (nextPos->x / PIXEL_SCALE - 2) * PIXEL_SCALE;  //-= 2 * PIXEL_SCALE;
            return;
          } else {  // if (nextPos->y / PIXEL_SCALE >= SCREENLEFT) {
            Rect r = Rect(nextPos->x / PIXEL_SCALE + 4, nextPos->y / PIXEL_SCALE - 6, CRAWLER_HEIGHT, CRAWLER_WIDTH);
            rotationCollision = rotationCollision || (arduboy.collide(r, block) || r.y < SCREENLEFT);

            r = Rect(enemy->animation.pos.x / PIXEL_SCALE + enemy->animation.sprite->dx, enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy - 1, CRAWLER_WIDTH, 1);
            grip = grip || arduboy.collide(r, block);  // || r.y <= SCREENLEFT);
            // arduboy.drawRect(r.x - cameraOffset, r.y, r.width, r.height);
          }
        } else if (enemy->animation.frame == CRAWLER_LEFT) {
          if (temp.v == BOTTOM) {
            setCrawlerDirection(enemy, Direction::left);
            nextVel->x = 0;
            nextPos->x = (nextPos->x / PIXEL_SCALE + 2) * PIXEL_SCALE;  //+= 2 * PIXEL_SCALE;
            nextPos->y = (nextPos->y / PIXEL_SCALE - 1) * PIXEL_SCALE;  //-= 1 * PIXEL_SCALE;
            return;
          } else {
            Rect r = Rect(nextPos->x / PIXEL_SCALE, nextPos->y / PIXEL_SCALE + 7, CRAWLER_HEIGHT, CRAWLER_WIDTH);
            rotationCollision = rotationCollision || (arduboy.collide(r, block) || r.y + CRAWLER_HEIGHT > SCREENRIGHT);

            r = Rect(enemy->animation.pos.x / PIXEL_SCALE + enemy->animation.sprite->dx, enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy + CRAWLER_HEIGHT, CRAWLER_WIDTH, 1);
            grip = grip || arduboy.collide(r, block);  // || r.y + CRAWLER_HEIGHT >= SCREENRIGHT);
            // arduboy.drawRect(r.x - cameraOffset, r.y, r.width, r.height);
          }
        }
      }
    }
  }

  if (enemy->type == EnemyType::fallingCrawler) return;

  if (!grip) {
    crawlerFall(enemy, nextVel);
    return;
  }

  if (rotationCollision) return;

  if (enemy->animation.frame == CRAWLER_UP) {
    setCrawlerDirection(enemy, Direction::down);
    nextPos->x = (nextPos->x / PIXEL_SCALE - 4) * PIXEL_SCALE;  //-= 4 * PIXEL_SCALE;
    nextPos->y = (nextPos->y / PIXEL_SCALE - 4) * PIXEL_SCALE;  //-= 4 * PIXEL_SCALE;
    nextVel->y = 0;
  } else if (enemy->animation.frame == CRAWLER_RIGHT) {
    setCrawlerDirection(enemy, Direction::left);
    nextPos->x = (nextPos->x / PIXEL_SCALE + 4) * PIXEL_SCALE;  //+= 4 * PIXEL_SCALE;
    nextPos->y = (nextPos->y / PIXEL_SCALE - 5) * PIXEL_SCALE;  //-= 5 * PIXEL_SCALE;
    nextVel->x = 0;
  } else if (enemy->animation.frame == CRAWLER_LEFT) {
    setCrawlerDirection(enemy, Direction::right);
    nextPos->x = (nextPos->x / PIXEL_SCALE - 4) * PIXEL_SCALE;  //-= 4 * PIXEL_SCALE;
    nextPos->y = (nextPos->y / PIXEL_SCALE + 3) * PIXEL_SCALE;  //+= 3 * PIXEL_SCALE;
    nextVel->x = 0;
  } else if (enemy->animation.frame == CRAWLER_DOWN) {
    setCrawlerDirection(enemy, Direction::up);
    nextPos->x = (nextPos->x / PIXEL_SCALE + 3) * PIXEL_SCALE;  //+= 3 * PIXEL_SCALE;
    nextPos->y = (nextPos->y / PIXEL_SCALE + 4) * PIXEL_SCALE;  //+= 4 * PIXEL_SCALE;
    nextVel->y = 0;
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
  if (activeGun == GunType::laser) return;
  for (uint8_t i = 0; i < AMMO_CAP; i++) {
    if (!bullet[i].active) continue;
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

bool checkLaserCollisions(Rect laser) {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (!enemy[i].animation.active) continue;
    if (Utils::collides(enemy[i].animation, laser)) {
      if (enemy[i].type != EnemyType::tortoise) {
        kill(&enemy[i], true);
      } else {
        return true;
      }
    }
  }
  return false;
}

void kill(enemy_t *enemy, bool shot) {
  enemy->animation.active = false;
  if (shot) {
    Particles::spawnExplosion(enemy->animation.pos,
                              enemy->animation.sprite->dx + enemy->animation.sprite->h / 2,
                              enemy->animation.sprite->dy + enemy->animation.sprite->w / 2);
    Powerups::spawn(HEART,
                    enemy->animation.pos.x / PIXEL_SCALE + enemy->animation.sprite->dx + enemy->animation.sprite->h / 2 - 3,
                    enemy->animation.pos.y / PIXEL_SCALE + enemy->animation.sprite->dy + enemy->animation.sprite->w / 2 - 3);
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
    enemy[currentEnemy].animation.dir = Direction::right;
    enemy[currentEnemy].hp = BAT_HP;
  } else if (type == EnemyType::worm) {
    enemy[currentEnemy].animation.sprite = &wormSprite;
    enemy[currentEnemy].hp = WORM_HP;
  } else if (type == EnemyType::tortoise) {
    enemy[currentEnemy].animation.sprite = &tortoiseSprite;
    enemy[currentEnemy].hp = TORTOISE_HP;
  } else if (type == EnemyType::crawler) {
    enemy[currentEnemy].animation.sprite = &crawlerSpriteUp;
    enemy[currentEnemy].hp = CRAWLER_HP;
    // enemy[currentEnemy].animation.dir = Direction::left;
    setCrawlerDirection(&enemy[currentEnemy], Direction::left);
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
    crawler->animation.sprite = &crawlerSpriteUp;
  } else if (dir == Direction::right) {
    crawler->animation.frame = CRAWLER_DOWN;
    crawler->animation.sprite = &crawlerSpriteDown;
  } else if (dir == Direction::up) {
    crawler->animation.frame = CRAWLER_RIGHT;
    crawler->animation.sprite = &crawlerSpriteRight;
  } else if (dir == Direction::down) {
    crawler->animation.frame = CRAWLER_LEFT;
    crawler->animation.sprite = &crawlerSpriteLeft;
  }
}

void crawlerFall(enemy_t *enemy, velocity_t *vel) {
  enemy->type = EnemyType::fallingCrawler;
  vel->x = 0;
  vel->y = 0;
}

void crawlerLand(enemy_t *enemy, velocity_t *vel) {
  enemy->type = EnemyType::crawler;
  vel->x = 0;
  vel->y = 0;
  setCrawlerDirection(enemy, Direction::left);
}

void onShiftMap() {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (!enemy[i].animation.active) continue;
    if (enemy[i].animation.pos.x < OFFSCREEN) {
      Level::shiftPos(&enemy[i].animation.pos);
    } else {
      enemy[i].animation.active = false;
    }
  }
}
}

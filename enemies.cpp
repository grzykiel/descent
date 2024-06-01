#include "enemies.h"
#include "bullet.h"


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
    }

    position_t nextPos = enemy[i].animation.pos;
    velocity_t nextVel = enemy[i].animation.vel;

    //TODO move to updatePosition
    if (enemy[i].type == EnemyType::worm || enemy[i].type == EnemyType::tortoise) {
      if (updateSprite(&enemy[i])) {
        uint8_t vel = enemy[i].type == EnemyType::worm ? 1 : 2;
        if (enemy[i].animation.dir == Direction::right) {
          if (nextPos.y / PIXEL_SCALE > SCREENRIGHT - enemy[i].animation.sprite->dy - enemy[i].animation.sprite->w - 2) {
            enemy[i].animation.dir = Direction::left;
          } else {
            nextVel.y = vel * PIXEL_SCALE;
          }
        } else {
          if (nextPos.y / PIXEL_SCALE < SCREENLEFT + 2) {  //} - enemy[i].animation.sprite->dy) {
            enemy[i].animation.dir = Direction::right;
          } else {
            nextVel.y -= vel * PIXEL_SCALE;
          }
        }
      } else {
        nextVel.y = 0;
      }
    } else {
      updateSprite(&enemy[i]);
    }

    updatePosition(enemy[i], &nextPos, &nextVel);
    checkCollisions(enemy[i], &nextPos, &nextVel);

    if (enemy[i].type == EnemyType::worm || enemy[i].type == EnemyType::tortoise) {
      if (nextVel.y == -1) {
        enemy[i].animation.dir = Direction::left;
        nextVel.y = 0;
      } else if (nextVel.y == 1) {
        enemy[i].animation.dir = Direction::right;
      }
    }

    if (enemy[i].type != EnemyType::blob) {
      if (nextVel.y > 0) {
        enemy[i].animation.dir = Direction::right;
      } else if (nextVel.y < 0) {
        enemy[i].animation.dir = Direction::left;
      }
    }

    enemy[i].animation.pos = nextPos;

    checkBulletCollisions(&enemy[i], &nextVel);
    enemy[i].animation.vel = nextVel;
  }
}

//TODO remove *nextPos
void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  int dx = player.animation.pos.x / PIXEL_SCALE - enemy.animation.pos.x / PIXEL_SCALE;
  int dy = player.animation.pos.y / PIXEL_SCALE - enemy.animation.pos.y / PIXEL_SCALE;
  if (enemy.type == EnemyType::blob) {
    if (dx > 0) {
      nextVel->x = min(++enemy.animation.vel.x, BLOB_MAX_VEL);
    } else if (dx < 0) {
      nextVel->x = max(--enemy.animation.vel.x, -BLOB_MAX_VEL);
    }

    if (dy > 0) {
      nextVel->y = min(++enemy.animation.vel.y, BLOB_MAX_VEL);
    } else if (dy < 0) {
      nextVel->y = max(--enemy.animation.vel.y, -BLOB_MAX_VEL);
    }
  } else if (enemy.type == EnemyType::bat) {
    nextVel->x = Utils::sign(dx) * BAT_VEL;
    nextVel->y = Utils::sign(dy) * BAT_VEL;
  } else if (enemy.type == EnemyType::worm || enemy.type == EnemyType::tortoise) {
    nextVel->x = max(nextVel->x + GRAVITY, -4 * PIXEL_SCALE);
  }

  nextPos->x += nextVel->x;
  nextPos->y += nextVel->y;
}

// tile collisions
void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel) {
  window_t wd = Utils::getCollisionWindow(enemy.animation.pos);

  for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        if (levelMap[i][j] == DASH) {
          if (enemy.type == EnemyType::blob) {
            continue;
          } else {
            block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE);
          }
        }
        collision_t temp = Utils::collisionCorrect(enemy.animation, nextPos, block);
        // set velocity according to collision
        if (temp.v == BOTTOM) {
          if (enemy.type == EnemyType::worm || enemy.type == EnemyType::tortoise) {
            if (j > 0) {
              if (!levelMap[i][j - 1]) {
                Rect edge = Rect((MAPHEIGHT - (i - 1) - 1) * BLOCKSIZE, (j - 1) * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
                if (Utils::collisionCorrect(enemy.animation, nextPos, edge).h == LEFT) {
                  nextVel->y = 1;
                }
              }
            }
            if (j < MAPWIDTH - 1) {
              if (!levelMap[i][j + 1]) {
                Rect edge = Rect((MAPHEIGHT - (i - 1) - 1) * BLOCKSIZE, (j + 1) * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
                if (Utils::collisionCorrect(enemy.animation, nextPos, edge).h == RIGHT) {
                  nextVel->y = -1;
                }
              }
            }
          } else {
            nextVel->x = 0;
          }
        } else if (temp.v == TOP) {
          nextVel->x = 0;
        }

        if (temp.h) nextVel->y = 0;


        if (enemy.type == EnemyType::worm || enemy.type == EnemyType::tortoise) {
          if (temp.h == LEFT) {
            nextVel->y = 1;
          } else if (temp.h == RIGHT) {
            nextVel->y = -1;
          }
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
        if (enemy->type == EnemyType::tortoise) return;
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



}
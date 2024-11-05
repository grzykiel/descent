#include "player.h"

sprite_t playerRunSprite = {
  Player::runRightSprite,
  Player::runLeftSprite,
  0,        //last frame
  nullptr,  //frame transitions
  0x01,     //offset
  0x68      //dim
};

const uint8_t jumpTransitions[5] PROGMEM = { 1, 15, 30, 45, 60 };
sprite_t playerJumpSprite = {
  Player::jumpRightSprite,
  Player::jumpLeftSprite,
  4,
  jumpTransitions,
  0x01,
  0x68
};
player_t player;

constexpr uint8_t walkAnimDelay = 6;
uint8_t maxHP;
uint8_t combo;
uint8_t power;

namespace Player {
void init() {
  player.animation.sprite = &playerJumpSprite;
  player.animation.active = true;
  player.animation.frame = FALL_FRAME;
  player.animation.t = 0;
  player.animation.iframe = 0;
  player.animation.pos.x = 112 * PIXEL_SCALE;  //128 * 3 * PIXEL_SCALE + 8;  //SCREENMID + 320;  //TODO #define
  player.animation.pos.y = 28 * PIXEL_SCALE;   //TODO #define
  player.animation.vel.x = 0;
  player.animation.vel.y = 0;
  player.animation.dir = Direction::right;
  player.hp = HP_INIT;
  maxHP = HP_INIT;

  combo = 0;
  power = 0;
  score = 0;
}


void update() {
  position_t nextPos = player.animation.pos;

  velocity_t nextVel = player.animation.vel;

  nextVel.x += GRAVITY;
  if (player.state == PlayerState::jumping) {
    if (player.animation.t == HALF_JUMP && arduboy.notPressed(A_BUTTON | B_BUTTON)) {
      nextVel.x = 0;
      fall();
    }
  }
  nextVel.x = max(nextVel.x, -2 * PIXEL_SCALE);  // TODO re#define terminal velocity

  nextPos.x += nextVel.x;
  nextPos.y += nextVel.y;

  //adjust for collisions
  checkEnemyCollisions(&nextPos, &nextVel);
  checkTileCollisions(&nextPos, &nextVel);


  //Boundary check
  if (nextPos.y / PIXEL_SCALE <= SCREENLEFT - (player.animation.sprite->offset & 0x0F)) {
    nextPos.y = SCREENLEFT;
    nextVel.y = 0;
  } else if (nextPos.y / PIXEL_SCALE > (SCREENRIGHT - ((player.animation.sprite->dim & 0xF0) >> 4) - (player.animation.sprite->offset & 0x0F))) {
    nextPos.y = (SCREENRIGHT - ((player.animation.sprite->dim & 0xF0) >> 4) - (player.animation.sprite->offset & 0x0F)) * PIXEL_SCALE;
    nextVel.y = 0;
  }

  checkPowerupCollisions(nextPos);

  player.animation.vel = nextVel;

  //check if falling
  if ((player.state == PlayerState::grounded) && (nextPos.x / PIXEL_SCALE < player.animation.pos.x / PIXEL_SCALE)) {
    fall();
  }

  player.animation.pos = nextPos;

  updateAnimation();
}

void updateAnimation() {
  if (player.state == PlayerState::grounded) {
    player.animation.t++;
    if (player.animation.vel.y != 0) {
      if (arduboy.everyXFrames(walkAnimDelay)) {
        player.animation.frame++;
        if (player.animation.frame >= N_WALKFRAMES) {
          player.animation.frame = 0;
        }
      }
    } else {
      player.animation.frame = 0;
    }
  } else {
    Utils::updateAnimation(&player.animation);
  }
}

void draw() {
  if (Utils::flickering(&player.animation)) return;
  if (player.animation.dir == Direction::left) {
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset, player.animation.pos.y / PIXEL_SCALE, player.animation.sprite->spriteL, player.animation.frame);
  } else {
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset, player.animation.pos.y / PIXEL_SCALE, player.animation.sprite->spriteR, player.animation.frame);
  }
}

void checkTileCollisions(position_t *nextPos, velocity_t *nextVel) {

  window_t wd = Utils::getCollisionWindow(player.animation.pos);

  for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (Level::getMap(i, j) == 0) continue;
      Rect block = Level::getMap(i, j) == DASH ? Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + DASH_OFFSET, j * BLOCKSIZE, DASH_HEIGHT, BLOCKSIZE) : Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
      collision_t type = Utils::collisionCorrect(player.animation, nextPos, block);
      if (type.v > NONE) {
        if (type.v == BOTTOM) {
          if (player.state != PlayerState::grounded) {
            Bullet::reload();
            Player::land();
            combo = 0;
          }
        } else if (type.v == TOP && Level::getMap(i, j) == BLOCK) {
          Level::destroyBlock(i, j);
        }
        nextVel->x = 0;
      }
      if (type.h == LEFT | type.h == RIGHT) {
        nextVel->y = 0;
      }
    }
  }
}

void checkEnemyCollisions(position_t *nextPos, velocity_t *nextVel) {
  if (player.animation.iframe != 0) return;
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (enemy[i].animation.active) {
      Rect enemyRect = Rect(enemy[i].animation.pos.x / PIXEL_SCALE + ((enemy[i].animation.sprite->offset & 0xF0) >> 4), enemy[i].animation.pos.y / PIXEL_SCALE + (enemy[i].animation.sprite->offset & 0x0F), enemy[i].animation.sprite->dim & 0x0F, (enemy[i].animation.sprite->dim & 0xF0) >> 4);
      // arduboy.drawRect(enemy[i].animation.pos.x/PIXEL_SCALE + enemy[i].animation.sprite->dx - cameraOffset, enemy[i].animation.pos.y/PIXEL_SCALE + enemy[i].animation.sprite->dy, enemy[i].animation.sprite->h, enemy[i].animation.sprite->w);
      collision_t type = Utils::collisionCorrect(player.animation, nextPos, enemyRect, true, true);

      if (type.v == BOTTOM) {
        if (enemy[i].type == EnemyType::crawler || enemy[i].type == EnemyType::fallingCrawler) {
          nextVel->x = KICKBACK_V;
          onDamaged();
        } else {
          bounce();
          nextVel->x = BOUNCE_VELOCITY;
          Bullet::reload();
          HUD::onRecharge();
          Enemies::kill(&enemy[i], false);
          combo++;
        }
      } else if (type.v == TOP) {
        nextVel->x = -KICKBACK_V;
        onDamaged();
      }

      if (type.h > NONE) {
        if (type.h == LEFT) {
          nextVel->y = KICKBACK_H;
        } else if (type.h == RIGHT) {
          nextVel->y = -KICKBACK_H;
        }
        onDamaged();
      }
    }
  }
}

void checkPowerupCollisions(position_t nextPos) {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    if (!powerup[i].active) continue;
    Rect pb = Rect(powerup[i].pos.x, powerup[i].pos.y, POWERUP_SIZE, POWERUP_SIZE);
    if (Utils::collides(player.animation, pb)) {
      onPickup(i);
    }
  }
}

void run(Direction dir) {
  player.animation.dir = dir;
  if (dir == Direction::right) {
    player.animation.vel.y = min(player.animation.vel.y + RUN_ACCEL, RUN_VELOCITY);
  } else if (dir == Direction::left) {
    player.animation.vel.y = max(player.animation.vel.y - RUN_ACCEL, -RUN_VELOCITY);
  }
}

void stop() {
  if (player.animation.vel.y < 0) {
    player.animation.vel.y = min(player.animation.vel.y + RUN_ACCEL, 0);
  } else if (player.animation.vel.y > 0) {
    player.animation.vel.y = max(player.animation.vel.y - RUN_ACCEL, 0);
  }
}

void jump() {
  player.animation.vel.x = JUMP_VELOCITY;
  player.animation.t = 0;
  player.state = PlayerState::jumping;
  player.animation.sprite = &playerJumpSprite;
  player.animation.frame = 0;
}

void bounce() {
  // player.animation.vel.x = BOUNCE_VELOCITY;
  player.animation.t = 30;
  player.state = PlayerState::bouncing;
  player.animation.sprite = &playerJumpSprite;  //TODO replace with bounce sprite
  player.animation.frame = 3;
}

void thrust(uint8_t multiplier) {
  player.animation.frame = 3;
  player.animation.t = 30;
  player.animation.vel.x = THRUST * multiplier;
}

void fall() {
  player.animation.vel.x = 0;
  player.animation.t = JUMP_TOP;

  player.state = PlayerState::falling;
  player.animation.sprite = &playerJumpSprite;
  player.animation.frame = FALL_FRAME;
}

void land() {
  player.state = PlayerState::grounded;
  player.animation.sprite = &playerRunSprite;
  triggerReleased = false;
}

void flicker() {
  player.animation.iframe = PLAYER_IFRAMES;
}

void onDamaged() {
  player.hp = max(player.hp - 1, 0);
  flicker();
  if (player.hp == 0) {
    Game::onDie();
  } else {
    HUD::onDamaged();
  }
  combo = 0;
  resetPower();
}

void onPickup(uint8_t type) {
  Powerups::collect(type);
  if (type == HEART) {
    player.hp = min(++player.hp, maxHP);
  } else if (type == HEART_UPGRADE) {
    maxHP = min(++maxHP, HP_CAP);
    player.hp = maxHP;
  } else if (type == SHOTGUN) {
    Bullet::setActiveGun(GunType::shot);
  } else if (type == LASER) {
    Bullet::setActiveGun(GunType::laser);
  } else if (type == MACHINEGUN) {
    Bullet::setActiveGun(GunType::automatic);
  } else if (type == AMMO_UPGRADE) {
    Bullet::increaseCap();
  }
}

void increaseCombo() {
  combo = min(combo + 1, 255);
}

void resetCombo() {
  if (combo > 5) {
    increasePower(1);
  } else if (combo > 10) {
    increasePower(2);
  } else if (combo > 20) {
    increasePower(3);
  }
}

void increasePower(uint8_t p) {
  if (p == 0) {
    power = min(power + 1, 3);
  } else {
    power = (power < p) ? p : power;
    power = min(power, 3);
  }
}

void resetPower() {
  power = 0;
}

}

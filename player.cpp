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

const uint8_t bounceTransitions[4] PROGMEM = { 15, 30, 45, 60 };
sprite_t playerBounceSprite = {
  Player::bounceRightSprite,
  Player::bounceLeftSprite,
  3,
  bounceTransitions,
  0x01,
  0x68
};

player_t player;

constexpr uint8_t walkAnimDelay = 6;
uint8_t maxHP;
uint8_t combo;
uint8_t power;
bool firstLanded;

namespace Player {
void init() {
  player.state = PlayerState::falling;
  player.animation.sprite = &playerJumpSprite;
  player.animation.active = true;
  player.animation.frame = FALL_FRAME;
  player.animation.t = JUMP_TOP;
  player.animation.iframe = 0;
  player.animation.pos.x = BLOCKSIZE * PIXEL_SCALE * (MAPHEIGHT + 1);
  player.animation.pos.y = PLAYER_START_Y * PIXEL_SCALE;  
  player.animation.vel.x = 0;
  player.animation.vel.y = 0;
  player.animation.dir = Direction::right;
  player.hp = HP_INIT;
  maxHP = HP_INIT;

  combo = 0;
  power = 0;
  score = 0;
  firstLanded = false;
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
  nextVel.x = max(nextVel.x, TERMINAL_VELOCITY * PIXEL_SCALE);

  nextPos.x += nextVel.x;
  if (firstLanded) nextPos.x = min(nextPos.x, CEILING);

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
  if (Utils::flickering(&player.animation.iframe)) return;
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
    if (!enemy[i].animation.active) continue;
    Rect enemyRect = Rect(enemy[i].animation.pos.x / PIXEL_SCALE + (enemy[i].animation.sprite->offset >> 4),
                          enemy[i].animation.pos.y / PIXEL_SCALE + (enemy[i].animation.sprite->offset & 0x0F),
                          enemy[i].animation.sprite->dim & 0x0F, enemy[i].animation.sprite->dim >> 4);
    collision_t type = Utils::collisionCorrect(player.animation, nextPos, enemyRect);

    if (type.v == BOTTOM) {
      if (enemy[i].type == EnemyType::crawler || enemy[i].type == EnemyType::fallingCrawler) {
        nextVel->x = KICKBACK_V;
        onDamaged();
      } else {
        bounce();
        nextVel->x = BOUNCE_VELOCITY;
        Bullet::reload();
        Enemies::kill(&enemy[i], false);
        increaseCombo();
        continue;
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

void checkPowerupCollisions(position_t nextPos) {
  for (uint8_t i = 0; i < 2; i++) {
    if (upgrade[i].type == INACTIVE) continue;
    Rect pb = Rect(upgrade[i].pos.x, upgrade[i].pos.y, UPGRADE_SIZE, UPGRADE_SIZE);
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
  Sound::playSweep(200, 1500, 15);
}

void bounce() {
  player.state = PlayerState::bouncing;
  player.animation.t = 0;
  player.animation.frame = 0;
  player.animation.sprite = &playerBounceSprite;
}

void thrust(uint8_t multiplier) {
  player.animation.t = 0;
  player.animation.frame = 0;
  player.animation.sprite = &playerBounceSprite;
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
  if (!firstLanded) {
    firstLanded = true;
    Sound::playIntro();
  }

  player.state = PlayerState::grounded;
  player.animation.sprite = &playerRunSprite;
  triggerReleased = false;
  player.animation.frame = 0;

  Player::onComboEnd();
  HUD::onComboEnd();
  Particles::onComboEnd();
}

void flicker() {
  player.animation.iframe = PLAYER_IFRAMES;
}

void onDamaged() {
  player.hp = max(player.hp - 1, 0);
  flicker();
  if (player.hp == 0) {
    Game::onDie();
    return;
  } else {
    HUD::onDamaged();
  }
  resetCombo();
  resetPower();
  Sound::playNoise(220, 1020, 6);
}

void onPickup(uint8_t p) {
  if (upgrade[p].type == HEART) {
    player.hp = min(player.hp + 1, maxHP);
  } else if (upgrade[p].type == HEART_CONTAINER) {
    maxHP = min(maxHP + 1, HP_CAP);
  } else if (upgrade[p].type == SHOTGUN) {
    Bullet::setActiveGun(GunType::shot);
  } else if (upgrade[p].type == LASER) {
    Bullet::setActiveGun(GunType::laser);
  } else if (upgrade[p].type == MACHINEGUN) {
    Bullet::setActiveGun(GunType::machine);
  } else if (upgrade[p].type == AMMO_CONTAINER) {
    Bullet::increaseCap();
  }
  Powerups::collect(p);
  Sound::playNoise(2000, 4000, 10);
  score += 5 * SCORE_MULTIPLIER;
}

void increaseCombo() {
  combo = min(combo + 1, 255);
  Sound::onIncreaseCombo();
}

void onComboEnd() {
  if (combo > 5) {
    increasePower(1);
  } else if (combo > 10) {
    increasePower(2);
  } else if (combo > 20) {
    increasePower(3);
  }
  score += combo * SCORE_MULTIPLIER;
}

void resetCombo() {
  combo = 0;
  Sound::onResetCombo();
}

void increasePower(uint8_t p) {
  Sound::playNoise(2000, 4000, 10);
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

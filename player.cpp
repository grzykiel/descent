#include "player.h"

#include "game.h"
// #include "levels.h"
#include "bitmaps.h"
#include "enemies.h"
// #include "enums.h"

sprite_t playerRunSprite = {
  Player::runRightSprite,
  Player::runLeftSprite,
  0,        //last frame
  nullptr,  //frame transitions
  0,        //dx
  1,        //dy
  6,        //w
  8         //h
};

uint8_t jumpTransitions[5] = { 1, 15, 30, 45, 60 };
sprite_t playerJumpSprite = {
  Player::jumpRightSprite,
  Player::jumpLeftSprite,
  4,
  jumpTransitions,
  0,
  1,
  6,
  8
};
player_t player;  //TODO initialise

const int8_t walkSpeed = 1;
const uint8_t walkAnimDelay = 6;

namespace Player {
void init() {
  player.animation.sprite = &playerJumpSprite;
  player.animation.active = true;
  player.animation.frame = FALL_FRAME;
  player.animation.t = 0;
  player.animation.pos.x = 128 * 3 * PIXEL_SCALE + 8;  //SCREENMID + 320;  //TODO #define
  player.animation.pos.y = 28 * PIXEL_SCALE;           //TODO #define
  player.animation.vel.x = 0;
  player.animation.vel.y = 0;

  player.animation.dir = Direction::right;

  Bullet::init();
}


void update() {
  position_t nextPos = player.animation.pos;

  velocity_t nextVel = player.animation.vel;
  nextVel.x = max(nextVel.x, -8 * PIXEL_SCALE);

  // physics update
  if (movementMode == PLATFORM) {
    nextVel.x += GRAVITY;
    if (player.state == PlayerState::jumping) {
      if (player.animation.t == HALF_JUMP && arduboy.notPressed(A_BUTTON | B_BUTTON)) {
        nextVel.x = 0;
        fall();
      }
    }
  }

  nextPos.x += nextVel.x;
  nextPos.y += nextVel.y;

  //Boundary check
  if (nextPos.y / PIXEL_SCALE <= SCREENLEFT - player.animation.sprite->dy) {
    nextPos.y = SCREENLEFT;
    nextVel.y = 0;
  } else if (nextPos.y / PIXEL_SCALE > (SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy)) {
    nextPos.y = (SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy) * PIXEL_SCALE;
    nextVel.y = 0;
  }

  //adjust for collisions
  collision_t type = checkTileCollisions(player.animation, &nextPos);
  if (type.v > NONE) {
    if (type.v == BOTTOM) {
      if (player.state != PlayerState::grounded) {
        Bullet::reload();
        Player::land();
      }
    }
    nextVel.x = 0;
  }
  if (type.h == LEFT | type.h == RIGHT) {
    nextVel.y = 0;
  }



  player.animation.vel = nextVel;

  //check if falling
  if ((player.state == PlayerState::grounded) && (nextPos.x / PIXEL_SCALE < player.animation.pos.x / PIXEL_SCALE)) {
    fall();
  }

  checkEnemyCollisions(player.animation, &nextPos);

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
  if (player.animation.dir == Direction::left) {
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset, player.animation.pos.y / PIXEL_SCALE, player.animation.sprite->spriteL, player.animation.frame);
  } else {
    Sprites::drawSelfMasked(player.animation.pos.x / PIXEL_SCALE - cameraOffset, player.animation.pos.y / PIXEL_SCALE, player.animation.sprite->spriteR, player.animation.frame);
  }
}

collision_t checkTileCollisions(animation_t anim, position_t *next) {
  collision_t type = { NONE, NONE };

  window_t wd = Utils::getCollisionWindow(anim.pos);

  // tile collisions
  for (uint16_t i = wd.xMin; i <= wd.xMax; i++) {
    for (uint8_t j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = levelMap[i][j] == DASH ? Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE) : Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        collision_t temp = Utils::collisionCorrect(anim, next, block);
        if (temp.v) type.v = temp.v;
        if (temp.h) type.h = temp.h;
      }
    }
  }

  return type;
}

void checkEnemyCollisions(animation_t anim, position_t *next) {
  for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
    if (enemy[i].animation.active) {
      Rect enemyRect = Rect(enemy[i].animation.pos.x / PIXEL_SCALE + enemy[i].animation.sprite->dx, enemy[i].animation.pos.y / PIXEL_SCALE + enemy[i].animation.sprite->dy, enemy[i].animation.sprite->h, enemy[i].animation.sprite->w);
      // arduboy.drawRect(enemy[i].animation.pos.x/PIXEL_SCALE + enemy[i].animation.sprite->dx - cameraOffset, enemy[i].animation.pos.y/PIXEL_SCALE + enemy[i].animation.sprite->dy, enemy[i].animation.sprite->h, enemy[i].animation.sprite->w);
      collision_t type = Utils::collisionCorrect(anim, next, enemyRect);
      if (type.v == BOTTOM) {
        bounce();
        // thrust();
        enemy[i].animation.active = false;
      }
    }
  }
}

void run(Direction dir) {
  player.animation.dir = dir;
}

void jump() {
  player.animation.vel.x = JUMP_VELOCITY;
  player.animation.t = 0;
  player.state = PlayerState::jumping;
  player.animation.sprite = &playerJumpSprite;
  /*if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::jumpLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::jumpRightSprite;
  }*/
  player.animation.frame = 0;
}

void bounce() {
  player.animation.vel.x = BOUNCE_VELOCITY;
  player.animation.t = 0;
  player.state = PlayerState::bouncing;
  player.animation.sprite = &playerJumpSprite;  //TODO replace with bounce sprite
  /*if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::jumpLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::jumpRightSprite;
  }*/
  player.animation.frame = 0;
}

void thrust() {
  player.animation.vel.x = THRUST;
}

void fall() {
  player.animation.vel.x = 0;
  player.animation.t = JUMP_TOP;

  player.state = PlayerState::falling;
  player.animation.sprite = &playerJumpSprite;
  /*if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::jumpLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::jumpRightSprite;
  }*/
  player.animation.frame = FALL_FRAME;
}

void land() {
  player.state = PlayerState::grounded;
  player.animation.sprite = &playerRunSprite;
  /*if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::runLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::runRightSprite;
  }*/
}

}

#include "player.h"

#include "game.h"
#include "levels.h"
#include "bitmaps.h"
// #include "enums.h"

sprite_t playerRunSprite = {
  Player::runRightSprite,
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
  player.animation.sprite = &playerRunSprite;
  player.animation.active = true;
  player.animation.frame = 0;
  player.animation.t = 0;
  player.animation.x = SCREENMID + 128;  //TODO #define
  player.animation.y = 28;               //TODO #define

  //TODO move to initialisation
  player.vy = 0;
  player.vx = 0;
  player.dir = Direction::right;

  Bullet::init();
}


void update() {
  vector_t nextPos;
  float next_vx = max(player.vx, -8.0f);
  float next_vy = player.vy;

  // physics update
  if (movementMode == PLATFORM) {
    next_vx += JUMP_GRAVITY;
    if (!player.grounded) {
      if (player.animation.t == HALF_JUMP && arduboy.notPressed(A_BUTTON | B_BUTTON)) {
        // arduboy.setCursor(player.animation.x - cameraOffset + 9, player.animation.y);
        // arduboy.print("HALFJUMP");
        next_vx = 0.0f;
        fall();
      }
      // player.animation.t++;
    }
  }
  nextPos.x = round(player.animation.x + player.vx);
  nextPos.y = player.animation.y + player.vy;

  //Boundary check
  if (nextPos.y <= SCREENLEFT - player.animation.sprite->dy) {
    nextPos.y = SCREENLEFT;
    next_vy = 0;
  } else if (nextPos.y > (SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy)) {
    nextPos.y = SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy;
    next_vy = 0;
  }

  //adjust for collisions
  collision_t type = checkCollisions(player.animation, &nextPos);
  if (type.v > NONE) {
    if (type.v == BOTTOM) {
      if (!player.grounded) {
        Bullet::reload();
        Player::land();
      }
    }
    next_vx = 0.0f;
  }
  if (type.h == LEFT | type.h == RIGHT) {
    next_vy = 0.0f;
  }

  player.vx = next_vx;
  player.vy = next_vy;

  //check if falling
  if (player.grounded && (nextPos.x < player.animation.x)) {
    fall();
  }
  // if (nextPos.x < player.animation.x) player.grounded = false;

  player.animation.x = nextPos.x;
  player.animation.y = nextPos.y;

  // Animation update
  if (player.grounded) {
    player.animation.t++;
    if (player.vy != 0) {
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
  Sprites::drawSelfMasked(player.animation.x - cameraOffset, player.animation.y, player.animation.sprite->sprite, player.animation.frame);
}

collision_t checkCollisions(animation_t anim, vector_t *next) {
  collision_t type = { NONE, NONE };

  window_t wd = Utils::getCollisionWindow(player.animation.x, player.animation.y);

  // tile collisions
  for (int i = wd.xMin; i <= wd.xMax; i++) {
    for (int j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = levelMap[i][j] == DASH ? Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE) : Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        // Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        collision_t temp = Utils::collisionCorrect(anim, next, block);
        // type.v |= temp.v;
        // type.h |= temp.h;
        if (temp.v) type.v = temp.v;
        if (temp.h) type.h = temp.h;
      }
    }
  }

  return type;
}

void jump() {
  player.vx = JUMP_VELOCITY;
  player.animation.t = 0;
  player.grounded = false;
  player.animation.sprite = &playerJumpSprite;
  if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::jumpLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::jumpRightSprite;
  }
  player.animation.frame = 0;
}

void thrust() {
  player.vx = THRUST;
}

void fall() {
  player.vx = 0;
  player.animation.t = JUMP_TOP;

  player.grounded = false;
  player.animation.sprite = &playerJumpSprite;
  if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::jumpLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::jumpRightSprite;
  }
  player.animation.frame = FALL_FRAME;
}

void land() {
  player.grounded = true;
  player.animation.sprite = &playerRunSprite;
  if (player.dir == Direction::left) {
    player.animation.sprite->sprite = Player::runLeftSprite;
  } else {
    player.animation.sprite->sprite = Player::runRightSprite;
  }
}

}

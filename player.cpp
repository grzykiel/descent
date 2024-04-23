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
player_t player;      //TODO initialise
player_t playerNext;  //TODO remove


//sprite_t playerJumpSprite

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

  Bullet::init();  //TODO move to Game namespace
}


void update() {
  vector_t nextPos;
  float next_vx = player.vx;
  float next_vy = player.vy;

  // physics update
  if (movementMode == PLATFORM) {
    next_vx += JUMP_GRAVITY;
  }
  nextPos.x = player.animation.x + player.vx;
  nextPos.y = player.animation.y + player.vy;

  //TODO gravity and kinematic movement

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
    if (type.v == BOTTOM) Bullet::reload();
    next_vx = 0;
  } 
  if (type.h == LEFT | type.h == RIGHT) {
    next_vy = 0;
  }
  
  player.vx = next_vx;
  player.vy = next_vy;

  player.animation.x = nextPos.x;
  player.animation.y = nextPos.y;

  // Animation update
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
}

collision_t checkCollisions(animation_t anim, vector_t *next) {
  collision_t type = {NONE, NONE};

  window_t wd = Utils::getCollisionWindow(player.animation.x, player.animation.y);

  // tile collisions
  for (int i = wd.xMin; i <= wd.xMax; i++) {
    for (int j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = levelMap[i][j] == DASH ? Rect((MAPHEIGHT - i - 1) * BLOCKSIZE + 6, j * BLOCKSIZE, 2, BLOCKSIZE) : Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        // Rect block = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        collision_t temp = Utils::collisionCorrect(anim, next, block);
        type.v |= temp.v;
        type.h |= temp.h;
      }
    }
  }

  return type;
}




}

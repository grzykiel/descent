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
player_t player; //TODO initialise
player_t playerNext;//TODO remove


//sprite_t playerJumpSprite

const int8_t walkSpeed = 1;
const uint8_t walkAnimDelay = 6;


namespace Player {
void init() {
  player.animation.sprite = &playerRunSprite;
  player.animation.active = true;
  player.animation.frame = 0;
  player.animation.t = 0;
  player.animation.x = SCREENMID + 128; //TODO #define
  player.animation.y = 28;              //TODO #define

  //TODO move to initialisation
  player.vy = 0;
  player.vx = 0;
  player.dir = Direction::right;

  Bullet::init(); //TODO move to Game namespace
}


void update() {
  vector_t nextPos;
  vector_t nextVel;

  // physics update
  nextPos.x = player.animation.x + player.vx;
  nextPos.y = player.animation.y + player.vy;

  //TODO gravity and kinematic movement

  //Boundary check
  if (nextPos.y <= SCREENLEFT - player.animation.sprite->dy) {
    nextPos.y = SCREENLEFT;
    nextVel.y = 0;
  } else if (nextPos.y > (SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy)) {
    nextPos.y = SCREENRIGHT - player.animation.sprite->w - player.animation.sprite->dy;
    nextVel.y = 0;
  }

  uint8_t type = checkCollisions(player.animation, &nextPos);
  switch (type) {
    case (TOP | BOTTOM):
      nextVel.x = 0;
      break;
    case (LEFT | RIGHT):
      nextVel.y = 0;
      break;
    case (TOPLEFT | TOPRIGHT | BOTTOMLEFT | BOTTOMRIGHT):
      nextVel.x = 0;
      nextVel.y = 0;
      break;
  };
  
  player.vx = nextVel.x;
  player.vy = nextVel.y;

  player.animation.x = nextPos.x;
  player.animation.y = nextPos.y;



  /*
  

  player.y = playerNext.y;
  player.x = playerNext.x;

  // Animation update
  if (player.vy != 0) {
    if (arduboy.everyXFrames(walkAnimDelay)) {
      player.frame++;
      if (player.frame >= N_WALKFRAMES) {
        player.frame = 0;
      }
    }
  } else {
    player.frame = 0;
  }*/
}

uint8_t checkCollisions(animation_t anim, vector_t *next) {
  uint8_t type = NONE;  

  window_t wd = Utils::getCollisionWindow(player.animation.x, player.animation.y);

  // tile collisions
  for (int i = wd.xMin; i <= wd.xMax; i++) {
    for (int j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        Rect block = levelMap[i][j] == DASH ? Rect((MAPHEIGHT-i-1)*BLOCKSIZE + 6, j*BLOCKSIZE, 2, BLOCKSIZE) :
        Rect((MAPHEIGHT-i-1) * BLOCKSIZE, j*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        type += collisionCorrect(anim, next, block);
      }
    }
  }
}

uint8_t collisionCorrect(animation_t anim, vector_t *next, Rect collider) {
  uint8_t type = NONE;
  Rect rect = Rect(anim.x + anim.sprite->dx, next->y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.y < rect.y) {
      type += LEFT;
      next->y = collider.y + collider.height - anim.sprite->dy;
    } else if (rect.y < collider.y) {
      type += RIGHT;
      next->y = collider.y - anim.sprite->w - anim.sprite->dy;
    }
  }

  rect = Rect(next->x + anim.sprite->dx, anim.y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < rect.x) {
      type += BOTTOM;
      next->x = collider.x + collider.width - anim.sprite->dx;
    } else if (rect.x < collider.x) {
      type += TOP;
      next->x = collider.x - anim.sprite->h - anim.sprite->dx;
    }
  }

  return type;
}


/*
//TODO remove
void collisionCheck() {
  
  window_t wd = Utils::getCollisionWindow(player.x, player.y);

  for (int i = wd.xMin; i <= wd.xMax; i++) {
    for (int j = wd.yMin; j <= wd.yMax; j++) {
      if (levelMap[i][j]) {
        if (levelMap[i][j] == DASH) {
          Rect blockRect = Rect((MAPHEIGHT-i-1)*BLOCKSIZE + 6, j*BLOCKSIZE, 2, BLOCKSIZE);
          collisionCorrect(blockRect);
        } else {
        Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
          collisionCorrect(blockRect);
        }
      }
    }
  }
}

void correctCollision(animation_t anim, vector_t *next, Rect collider) {
  Rect rect = Rect(anim.x + anim.sprite->dx, next->y + anim.sprite->dy, anim.sprite->h, anim.sprite->h);
  if (arduboy.collide(rect, collider)) {
    if (collider.y < rect.y) {
      next->y = collider.y + collider.width - anim.sprite->dy;
    } else if (rect.y < collider.y) {
      next->y = collider.y - anim.sprite->w - anim.sprite->dy;
    }
  }


  rect = Rect(next->x + anim.sprite->dx, anim.y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < rect.x) {
      next->x = collider.x + collider.width - anim.sprite->dy;
    } else if (rect.x < collider.x) {
      next->x = collider.x - anim.sprite->h - anim.sprite->dy;
    }
  }
}

//TODO remove
void collisionCorrect(Rect collision) {
  Rect playerRect = Rect(player.x, playerNext.y+1, BLOCKSIZE, PLAYER_WIDTH);
  if (arduboy.collide(playerRect, collision)) {
    if (collision.y < playerRect.y) {
      playerNext.y = collision.y + collision.width - 1;
      player.vy = 0;
    } else if (playerRect.y < collision.y) {
      playerNext.y = collision.y - PLAYER_WIDTH-1;
      player.vy = 0;
    }
  }

  playerRect = Rect(playerNext.x, player.y+1, BLOCKSIZE, PLAYER_WIDTH);
  if (arduboy.collide(playerRect, collision)) {
    if (collision.x < playerRect.x) {
      playerNext.x = collision.x + collision.width;
    } else if (playerRect.x < collision.x) {
      playerNext.x = collision.x - PLAYER_HEIGHT;
    }
  }
}*/

}

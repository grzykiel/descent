#include "player.h"

#include "game.h"
#include "levels.h"
#include "bitmaps.h"
// #include "enums.h"

player_t player;
player_t playerNext;

const int8_t walkSpeed = 1;
const uint8_t walkAnimDelay = 6;


namespace Player {
void init() {
  player.y = 28;
  player.x = SCREENMID + 128; //TODO #define
  player.vy = 0;
  player.vx = 0;
  player.dir = Direction::right;
  player.sprite = Player::runRightSprite;
  player.frame = 0;

  Bullet::init();
}


void update() {
  playerNext.y = player.y + player.vy;
  playerNext.x = player.x + player.vx;

  // Boundary checking
  if (playerNext.y <= SCREENLEFT) {
    playerNext.y = SCREENLEFT;
    player.vy = 0;
  } else if (playerNext.y > (SCREENRIGHT - PLAYER_WIDTH)) {
    playerNext.y = SCREENRIGHT - PLAYER_WIDTH;
    player.vy = 0;
  }

  collisionCheck();

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
  }
}

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



void collisionCorrect(Rect collision) {

  Rect playerRect = Rect(player.x, playerNext.y+1, BLOCKSIZE, PLAYER_WIDTH);
  if (arduboy.collide(playerRect, collision)) {
    if (collision.y < playerRect.y) {
      playerNext.y = collision.y + collision.height-1;
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
}
}

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
  player.x = SCREENMID + 128;
  player.vy = 0;
  player.vx = 0;
  player.dir = Direction::right;
  player.sprite = Player::runRightSprite;
  player.frame = 0;
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
  int yMin = max(floor(player.y / BLOCKSIZE) - 1, 0);
  int yMax = min(ceil(player.y / BLOCKSIZE) + 1, MAPWIDTH - 1);


  int xMin = ceil(player.x / (1.0f * BLOCKSIZE)) + 1;
  int xMax = floor(player.x / (1.0f * BLOCKSIZE)) - 1;
  xMin = max(MAPHEIGHT - 1 - xMin, 0);
  xMax = min(MAPHEIGHT - 1 - xMax, MAPHEIGHT - 1);



  for (int i = xMin; i <= xMax; i++) {
    for (int j = yMin; j <= yMax; j++) {
      // Sprites::drawSelfMasked((SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, Tiles::block, sandbox[i][j]);
      if (scrollLevel[i][j]) {
        Rect blockRect = Rect((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
        // arduboy.drawRect(blockRect.x, blockRect.y, BLOCKSIZE, BLOCKSIZE, WHITE);
        collisionCorrect(blockRect);
      }
    }
  }
}

void collisionCorrect(Rect collision) {

  Rect playerRect = Rect(player.x, playerNext.y, BLOCKSIZE, BLOCKSIZE);
  if (arduboy.collide(playerRect, collision)) {
    if (collision.y < playerRect.y) {
      playerNext.y = collision.y + collision.height;
      player.vy = 0;
    } else if (playerRect.y < collision.y) {
      playerNext.y = collision.y - collision.height;
      player.vy = 0;
    }
  }

  playerRect = Rect(playerNext.x, player.y, BLOCKSIZE, BLOCKSIZE);
  if (arduboy.collide(playerRect, collision)) {
    if (collision.x < playerRect.x) {
      playerNext.x = collision.x + collision.height;
    } else if (playerRect.x < collision.x) {
      playerNext.x = collision.x - collision.height;
    }
  }
}
}
#include "player.h"

#include "game.h"
#include "levels.h"
#include "bitmaps.h"
// #include "enums.h"

player_t player;
player_t playerNext;

namespace Player {
void init() {
  player.y = 28;
  player.x = 64;
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
}

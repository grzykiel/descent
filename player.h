#ifndef PLAYER_H
#define PLAYER_H
#include "enums.h"
#include <math.h>
#include "levels.h"
#endif

typedef struct {
  int8_t y = 28;
  int8_t x = 64;
  int8_t vy = 0;
  int8_t vx = 0;
  Direction dir = Direction::right;
  const unsigned char *sprite = Player::runRightSprite;
  uint8_t frame = 0;
} player_t;

player_t player;

player_t playerNext;


namespace Player {
void update();
void draw();

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
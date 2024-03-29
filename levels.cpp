#include "levels.h"

#include "game.h"
#include "player.h"
#include "bitmaps.h"

uint8_t sandbox[SCREENHEIGHT][SCREENWIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};

namespace Level {

void drawLevel() {
  for (int i = 0; i < SCREENHEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      Sprites::drawSelfMasked((SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, Tiles::block, sandbox[i][j]);
    }
  }
}

}
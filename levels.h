#ifndef LEVELS_H
#define LEVELS_H
#include "globals.h"
#include "player.h"
#include "enemies.h"
#include "hud.h"
#include "game.h"
#include "bitmaps.h"
#include "particles.h"
#include "powerups.h"

#define WALL_WIDTH_MAX 4
#define DASH_WIDTH_MIN 2
#define DASH_WIDTH_MAX 4
#define MIN_GAP 2

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 2

namespace Level 
{
  void init();
  void draw();
  void update();

  void shiftMap();
  void copyRoom(uint8_t from[], uint8_t f, uint8_t toMap[], uint8_t t);
  void eraseRoom();

  void generateWalls(bool left);
  
  void autoTile();
  
  void generateDashes();
  void placeDashes(uint8_t row, uint8_t cs, uint8_t ce);

  void generateBlocks();

  void generateEnemies();

  void destroyBlock(int16_t i, uint8_t j);

  void shiftPos(position_t *pos);

  uint8_t getMap(int16_t i, uint8_t j);
  uint8_t getRoom(uint8_t room[], int16_t i, uint8_t j);

  void writeMap(int16_t i, uint8_t j, uint8_t tile);
  void writeRoom(uint8_t room[], int16_t i, uint8_t j, uint8_t tile);

}

#endif






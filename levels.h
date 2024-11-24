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

#define PASSAGE_MIN 2
#define DASH_MIN 0
#define DASH_MAX 8
#define BLOCKS_MAX 4
#define NARROW_INTERVAL 4

#define PBAT_MAX 50
#define PCRAWLER_MAX 50
#define MIN_ENEMIES_PER_ROOM 1
#define MAX_ENEMIES_PER_ROOM 3

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 2

extern uint8_t pbat;
extern uint8_t pcrawler;
extern uint16_t kills;

namespace Level 
{
  void init();
  void draw();
  void update();

  void shiftMap();
  void copyRoom(uint8_t from[], uint8_t f, uint8_t toMap[], uint8_t t);
  void eraseRoom();

  void generateWall(bool left, uint8_t edge);
  
  void autoTile();
  
  void generateDashes();
  bool clearPath(uint8_t x, uint8_t y1, uint8_t y2);

  void generateBlocks();

  void generateEnemies();
  void generateFlying();
  void generateCrawling();
  void generateCrawler();

  void destroyBlock(int16_t i, uint8_t j);

  void shiftPos(position_t *pos);

  uint8_t getMap(int16_t i, uint8_t j);
  uint8_t getRoom(uint8_t room[], int16_t i, uint8_t j);

  void writeMap(int16_t i, uint8_t j, uint8_t tile);
  void writeRoom(uint8_t room[], int16_t i, uint8_t j, uint8_t tile);

}

#endif






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

#define PASSAGE_MIN       2
#define PASSAGE_MIN_INIT  5
#define PASSAGE_MAX_INIT  8
#define DASHES_INIT       0x03
#define BLOCKS_MAX        4
#define ROOM_SHRINK_FREQ  4

#define ENEMIES_INIT          1
#define PBAT_INIT             20
#define PBAT_MAX              80
#define PCRAWLER_INIT         0
#define PCRAWLER_MAX          80
#define PTORTOISE_INIT        0
#define PTORTOISE_MAX         60
#define MAX_ENEMIES_PER_ROOM  5
#define ENEMY_INCR_FREQ       5

#define MAX_ATTEMPTS  128

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
  void increaseBatProbability();
  void increaseTortoiseProbability();
  void increaseCrawlerProbability();
  void onKill();
  void debugDisplay(); //TODO REMOVE
}

#endif






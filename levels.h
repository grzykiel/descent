#ifndef LEVELS_H
#define LEVES_H
#include "globals.h"

#define MAPWIDTH 8
#define MAPHEIGHT 48

#define WALL_WIDTH_MAX 4
#define MIN_GAP 2


#define TOP_MARGIN    1
#define BOTTOM_MARGIN 2


extern uint8_t nextRoom[SCREENHEIGHT][SCREENWIDTH];
extern uint8_t levelMap[MAPHEIGHT][MAPWIDTH];

namespace Level 
{
  void init();
  void draw();
  void update();

  void shiftMap();
  void copyMap(uint8_t fromMap[][MAPWIDTH], uint8_t fromIndex, uint8_t toMap[][MAPWIDTH], uint8_t toIndex);
  void eraseRoom(uint8_t room[][SCREENWIDTH]);

  void generateWalls(uint8_t room[][SCREENWIDTH], bool left);

  void autoTile(uint8_t room[][SCREENWIDTH]);

  void generateDash(uint8_t room[][SCREENWIDTH]);
  void fillDashLine(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce);
  void deleteTwo(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce);
  void fillDashRandom(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce);


}

#endif






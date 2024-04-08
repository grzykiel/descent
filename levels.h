#ifndef LEVELS_H
#define LEVES_H
#include "globals.h"

#define MAPWIDTH 8
#define MAPHEIGHT 48

#define WALL_WIDTH_MAX 4


extern uint8_t nextRoom[SCREENHEIGHT][SCREENWIDTH];
extern uint8_t levelMap[MAPHEIGHT][MAPWIDTH];

namespace Level 
{
  void init();
  void draw();
  void update();

  void shiftMap();
  void copyMap(uint8_t fromMap[][MAPWIDTH], uint8_t fromIndex, uint8_t toMap[][MAPWIDTH], uint8_t toIndex);

  void generateWalls(uint8_t room[][SCREENWIDTH], bool left);

  void autoTile(uint8_t room[][SCREENWIDTH]);

  void eraseRoom(uint8_t room[][SCREENWIDTH]);

}

#endif






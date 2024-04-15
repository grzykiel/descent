#ifndef LEVELS_H
#define LEVES_H
#include "globals.h"



#define WALL_WIDTH_MAX 4
#define DASH_WIDTH_MIN 2
#define DASH_WIDTH_MAX 4
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
  
  void generateDashes(uint8_t room[][SCREENWIDTH]);
  void placeDashes(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce);

  void generateBlocks(uint8_t room[][SCREENWIDTH]);

}

#endif






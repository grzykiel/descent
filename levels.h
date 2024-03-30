#ifndef LEVELS_H
#define LEVES_H
#include "globals.h"



#define MAPWIDTH 8
#define MAPHEIGHT 48


extern uint8_t sandbox[SCREENHEIGHT][SCREENWIDTH];
extern uint8_t scrollLevel[MAPHEIGHT][MAPWIDTH];

namespace Level 
{
  void init();

  void drawLevel();

  void copyMap(uint8_t fromMap[][MAPWIDTH], uint8_t fromIndex, uint8_t toMap[][MAPWIDTH], uint8_t toIndex);
}

#endif






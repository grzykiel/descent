#ifndef LEVELS_H
#define LEVES_H
#include "globals.h"
// #include "bitmaps.h"


#define MAPWIDTH 8
#define MAPHEIGHT 48


extern uint8_t sandbox[SCREENHEIGHT][SCREENWIDTH];
extern uint8_t scrollLevel[MAPHEIGHT][MAPWIDTH];

namespace Level 
{
  void drawLevel();
}

#endif






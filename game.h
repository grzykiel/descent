#ifndef GAME_H
#define GAME_H

#include "globals.h"

#include "controls.h"


namespace Game
{
  void loop();
  void input();
  void update();
  void draw();
  void updateCamera();

  bool updateSprite(sprite_t *sprite);
}

#endif
   


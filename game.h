#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "bullet.h"

#include "controls.h"


namespace Game {
  void loop();
  void input();
  void update();
  void draw();
  void updateCamera();

  bool updateAnimation(animation_t *animation);
  bool collides(animation_t anim, Rect block);
  
}

#endif

#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "bullet.h"
#include "controls.h"
#include "hud.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"
#include "bitmaps.h"
#include "powerups.h"

namespace Game {
  void loop();
  void input();
  void init();
  void update();
  void draw();
  void updateCamera();
  void onDie();
}

#endif

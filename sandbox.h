#ifndef SANDBOX_H
#define SANDBOX_H

#include "globals.h"
#include "player.h"
#include "controls.h"
#include "game.h"

#define SANDBOX_HEIGHT 16

namespace Sandbox
{
  void init();
  void loop();
  void input();
  void update();
  void draw();

  void shoot();
  void updateBullets();
  void drawBullets();
  void drawMuzzleFlash();

}

extern uint8_t sandbox[SANDBOX_HEIGHT][SCREENWIDTH];

extern int camera;


#endif
   
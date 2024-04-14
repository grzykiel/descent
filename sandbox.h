#ifndef SANDBOX_H
#define SANDBOX_H

#include "globals.h"
#include "player.h"
#include "controls.h"

#define SANDBOX_HEIGHT 16

namespace Sandbox
{
  void init();
  void loop();
  void input();
  void update();
  void draw();

  void drawMuzzleFlash();
  void shoot();
}

extern uint8_t sandbox[SANDBOX_HEIGHT][SCREENWIDTH];

extern int camera;


#endif
   
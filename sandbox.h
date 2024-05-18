#ifndef SANDBOX_H
#define SANDBOX_H

#include "globals.h"
#include "player.h"
#include "controls.h"
#include "game.h"
#include "bullet.h"

#define SANDBOX_HEIGHT 16

namespace Sandbox
{
  void init();
  void loop();
  void input();
  void update();
  void draw();

  void drawMap();
  void drawBlob();

  void collisionCheck();
  void velocityUpdate();


  void basicUpdate();
}

extern uint8_t sandbox[SANDBOX_HEIGHT][SCREENWIDTH];

extern int camera;




typedef struct {
  int16_t x;
  int16_t y;
  int8_t vx;
  int8_t vy;
  int8_t dx;
  int8_t dy;
  uint8_t tx;
  uint8_t ty;
  uint8_t delta;
  bool frame;
} blob_t;

#endif
   
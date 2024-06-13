#include "sandbox.h"
#include "bitmaps.h"
#include "levels.h"

#define MIN_DELAY 30
#define MAX_DELAY 45

uint8_t sandbox[SANDBOX_HEIGHT][SCREENWIDTH] = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};

int camera = 0;

int8_t f = 0;
uint8_t maxF = 120;

uint8_t speed = 30;

uint8_t x,y;
uint8_t frame;



namespace Sandbox {
void loop() {
  input();
  update();
  draw();
}

void init() {
  Level::autoTile(sandbox);
}

void input() {

  if (arduboy.pressed(left_btn)) {
    y--;
  } else if (arduboy.pressed(right_btn)) {
    y++;
  }
  if (arduboy.pressed(up_btn)) {
    x++;
  } else if (arduboy.pressed(down_btn)) {
    x--;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    frame++;
  } else if (arduboy.justPressed(B_BUTTON)) {
    frame--;
  }

}

void update() {
  arduboy.fillRect(32, 32, 16, 16);
  Sprites::drawPlusMask(x, y, Particles::explosionSprite, frame);
}




void draw() {

}



}
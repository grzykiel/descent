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

  if (arduboy.justPressed(A_BUTTON)) {
    f = maxF;
  }
  if (arduboy.justPressed(up_btn)) {
    speed++;
  } else if (arduboy.justPressed(down_btn)) {
    speed--;
  }

  if (arduboy.justPressed(left_btn)) {
    maxF--;
  } else if (arduboy.justPressed(right_btn)) {
    maxF++;
  }
}

void update() {

}




void draw() {
  if (!flashing(&f)) arduboy.drawRect(60, 28, 8, 8);
  Utils::println(speed);
  Utils::println(maxF);
}

bool flashing(int8_t *f) {
  // arduboy.print(*f);
  if (*f == 0) return false;
  if (*f > 0) {
    *f = *f-1;
    // arduboy.print(*f);
  } else if (*f < 0) {
    *f = *f+1;
    // arduboy.print("false");
  }

  if (abs(*f)%speed == 0) {
    *f *= -1;
  }

  return (*f < 0);  
}


}
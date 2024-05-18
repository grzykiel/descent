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

int x = 64;
int y = 32;

uint8_t accel = 1;


blob_t jelly = {
  32*128,
  16*128,
  0,
  0,
  24,
  24,
  0,
  0,
  45,
  0
};



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
  /*if (arduboy.pressed(up_btn)) {
    jelly.vx = min(jelly.vx+1, MIN_DELAY);
  } else if (arduboy.pressed(down_btn)) {
    jelly.vx = max(jelly.vx-1, -MIN_DELAY);
  } else if (arduboy.pressed(left_btn)) {
    jelly.vy = max(jelly.vy-1, -MIN_DELAY);
  } else if (arduboy.pressed(right_btn)) {
    jelly.vy = min(jelly.vy+1, MIN_DELAY);
  }*/

  if (arduboy.pressed(up_btn)) {
    x++;
  } else if (arduboy.pressed(down_btn)) {
    x--;
  } else if (arduboy.pressed(left_btn)) {
    y--;
  } else if (arduboy.pressed(right_btn)) {
    y++;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    jelly.delta++;

  } else if (arduboy.justPressed(B_BUTTON)) {
    jelly.delta--;
  }
}

void update() {
  // velocityUpdate();
  basicUpdate();

  if (arduboy.everyXFrames(jelly.delta)) {
    jelly.frame = !jelly.frame;
  }

  collisionCheck();
}




void basicUpdate() {
  uint8_t maxVel = 8*4-1;
  if (x-jelly.x/128 > 0) {
    jelly.vx = min(jelly.vx+accel, maxVel);
  } else if (x-jelly.x/128 < 0) {
    jelly.vx = max(jelly.vx-accel, -maxVel);
  }
  jelly.x+=jelly.vx/4;

  if (y-jelly.y/128 > 0) {
    jelly.vy = min(jelly.vy+accel, maxVel);
  } else if (y-jelly.y/128 < 0) {
    jelly.vy = max(jelly.vy-accel, -maxVel);
  }
  jelly.y += jelly.vy/4;

  collisionCheck();
}

void velocityUpdate() {
  if (x - jelly.x > 0) {
    jelly.vx = min(jelly.vx + accel, 8);
  } else if (x - jelly.x < 0) {
    jelly.vx = max(jelly.vx - accel, -8);
  }

  if (y - jelly.y > 0) {
    jelly.vy = min(jelly.vy + accel, 8);
  } else if (y - jelly.y < 0) {
    jelly.vy = max(jelly.vy - accel, -8);
  }

  if (jelly.vx > 0) {
    if (jelly.vx < 128 - jelly.dx) {
      jelly.dx += jelly.vx;
    } else {
      jelly.x++;
      jelly.dx = jelly.dx - 128 + jelly.vx;
    }
  } else if (jelly.vx < 0) {
    if (jelly.vx > -127 - jelly.dx) {
      jelly.dx += jelly.vx;
    } else {
      jelly.x--;
      jelly.dx = jelly.dx + 128 + jelly.vx;
    }
  }

  if (jelly.vy > 0) {
    if (jelly.vy < 128 - jelly.dy) {
      jelly.dy += jelly.vy;
    } else {
      jelly.y++;
      jelly.dy = jelly.dy - 128 + jelly.vy;
    }
  } else if (jelly.vy < 0) {
    if (jelly.vy > -127 - jelly.dy) {
      jelly.dy += jelly.vy;
    } else {
      jelly.y--;
      jelly.dy = jelly.dy + 128 + jelly.vy;
    }
  }
}

void collisionCheck() {
  Point player = Point(x, y);
  Rect enemy = Rect(jelly.x/128+1, jelly.y/128, 6, 7);
  if (arduboy.collide(player, enemy)) {
    jelly.vx = -96;
  }
}

void draw() {
  drawBlob();

  drawMap();
}

void drawMap() {
  //draw map
  for (int i = 0; i < SANDBOX_HEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      if (sandbox[i][j])
        Sprites::drawSelfMasked((SANDBOX_HEIGHT - i - 1) * BLOCKSIZE - camera, j * BLOCKSIZE, Tiles::wall, sandbox[i][j]);
    }
  }
}


void drawBlob() {
  //"player"
  arduboy.drawRect(x, y, 1, 1, WHITE);

  //jelly
  // Sprites::drawSelfMasked(jelly.x, jelly.y, Enemies::blob, jelly.frame);
  Sprites::drawSelfMasked(jelly.x/128, jelly.y/128, Enemies::blob, jelly.frame);
}



}
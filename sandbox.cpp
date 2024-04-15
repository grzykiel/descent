#include "sandbox.h"
#include "bitmaps.h"
#include "levels.h"

uint8_t sandbox[SANDBOX_HEIGHT][SCREENWIDTH] = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};

int camera = 0;

namespace Sandbox {
void loop() {
  input();
  update();
  draw();
}

void init() {
  player.y = 28;
  player.x = 0;
  player.vy = 0;
  player.vx = 0;
  player.dir = Direction::right;
  player.sprite = Player::runRightSprite;
  player.frame = 0;

  Bullet::init();



  Level::autoTile(sandbox);
}

void input() {
  if (arduboy.pressed(left_btn)) {
    player.y -= 1;
  } else if (arduboy.pressed(right_btn)) {
    player.y += 1;
  }

  if (arduboy.pressed(up_btn)) {
    player.x += 1;
  } else if (arduboy.pressed(down_btn)) {
    player.x -= 1;
  }

  //Autotile testing
  /*if (arduboy.justPressed(A_BUTTON)) {
    Level::autoTile(sandbox);
  }
  if (arduboy.justPressed(B_BUTTON)) {
    Level::eraseRoom(sandbox);
    Level::generateWalls(sandbox, true);
    Level::generateWalls(sandbox, false);
  }*/

  //Shoot shoes
  if (arduboy.justPressed(A_BUTTON)) {
    shoot();
  }
}

void update() {
  camera = Util::trim(player.x - SCREENMID, 0, SANDBOX_HEIGHT * BLOCKSIZE - SCREENTOP);
  Bullet::updateBullets();
}

void draw() {
  //draw player
  Sprites::drawSelfMasked(player.x - camera, player.y, player.sprite, player.frame);

  //draw map
  for (int i = 0; i < SANDBOX_HEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      if (sandbox[i][j])
        Sprites::drawSelfMasked((SANDBOX_HEIGHT - i - 1) * BLOCKSIZE - camera, j * BLOCKSIZE, Tiles::wall, sandbox[i][j]);
    }
  }

  Bullet::draw();
  
}

void shoot() {
  //TODO: creat init functions. Move constants to global
  Bullet::shoot();
}




}
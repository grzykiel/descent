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

  Player::initMuzzleFlash();

  // init bullet
  bullet.active = false;
  bullet.sprite.sprite = ShootShoes::bullet;

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
  updateBullets();
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

  drawMuzzleFlash();
  drawBullets();
}

void shoot() {
  muzzleFlash.active = true;
  muzzleFlash.sprite.t = 0;
  muzzleFlash.sprite.frame = 0;

  bullet.active = true;
  bullet.x = player.x;
  bullet.y = player.y;
  bullet.sprite.frame = 0;
  bullet.t = 0;
  bullet.v = BULLET_START_VEL;
}

void drawMuzzleFlash() {
  if (muzzleFlash.active) {
    Sprites::drawSelfMasked(player.x - camera - MF_OFFSET, player.y, muzzleFlash.sprite.sprite, muzzleFlash.sprite.frame);
    muzzleFlash.sprite.t++;
    if (muzzleFlash.sprite.t == muzzleFlash.sprite.transitions[muzzleFlash.sprite.frame]) {
      muzzleFlash.sprite.frame++;
      if (muzzleFlash.sprite.frame == muzzleFlash.sprite.last) {
        muzzleFlash.active = false;
      }
    }
  }
}

void updateBullets() {
  if (bullet.active) {
    bullet.x = int(1.0f*bullet.x-bullet.v);
    bullet.v -= BULLET_ACCEL;
    if (bullet.t >= 40 | bullet.v <=0) {
      bullet.active = false;
    }
  }
}

void drawBullets() {
  if (bullet.active) {
    Sprites::drawSelfMasked(bullet.x - camera, bullet.y, bullet.sprite.sprite, bullet.sprite.frame);
  }
}

}
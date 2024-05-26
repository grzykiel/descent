#include "game.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"
#include "bitmaps.h"

namespace Game {
void loop() {
  input();
  update();
  draw();
}

void input() {
  if (arduboy.justPressed(left_btn)) {
    Player::run(Direction::left);   
  } else if (arduboy.justPressed(right_btn)) {

    Player::run(Direction::right);
  }

  if (arduboy.pressed(left_btn)) {
    player.animation.vel.y = -walkSpeed * PIXEL_SCALE;
  } else if (arduboy.pressed(right_btn)) {
    player.animation.vel.y = walkSpeed * PIXEL_SCALE - 1;
  } else if (arduboy.notPressed(left_btn | right_btn)) {
    player.animation.vel.y = 0;
  }

  if (movementMode == TOPDOWN) {
    if (arduboy.pressed(up_btn)) {
      player.animation.vel.x = walkSpeed * PIXEL_SCALE - 1;
    } else if (arduboy.pressed(down_btn)) {
      player.animation.vel.x = -walkSpeed * PIXEL_SCALE;
    } else if (arduboy.notPressed(up_btn | down_btn)) {
      player.animation.vel.x = 0;
    }
  }

  if (arduboy.justPressed(A_BUTTON)) {
    if (player.state != PlayerState::grounded) {
      Bullet::shoot();
    } else {
      Player::jump();
    }
  }


  //debug & tuning
  if (arduboy.justPressed(B_BUTTON)) {
    mapNumbers = !mapNumbers;
  }

  if (arduboy.justPressed(up_btn)) {
  } else if (arduboy.justPressed(down_btn)) {
  }

}

void update() {
  Player::update();
  Bullet::update();
  Enemies::update();
  Level::update();
  updateCamera();
}

void updateCamera() {
  cameraOffset = Utils::trim(player.animation.pos.x / PIXEL_SCALE - SCREENMID, 0, MAPHEIGHT * BLOCKSIZE - SCREENTOP);
}

void draw() {
  // draw player
  Player::draw();
  // arduboy.setCursor(player.animation.x - cameraOffset + 9, player.animation.y);
  // arduboy.print(player.animation.t);

  // draw level
  Level::draw();

  Bullet::draw();

  Enemies::draw();
}

}
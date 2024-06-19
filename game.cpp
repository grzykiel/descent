#include "game.h"

namespace Game {
void loop() {
  input();
  update();
  draw();
}

void init() {
  Player::init();
  Enemies::init();
  Level::init();
  Particles::init();
  Bullet::init();
}

void input() {
  if (arduboy.pressed(left_btn)) {
    Player::run(Direction::left);
  } else if (arduboy.pressed(right_btn)) {
    Player::run(Direction::right);
  } else if (arduboy.notPressed(left_btn | right_btn)) {
    Player::stop();
  }

  if (movementMode == TOPDOWN) {
    // if (arduboy.pressed(up_btn)) {
    //   player.animation.vel.x = walkSpeed * PIXEL_SCALE - 1;
    // } else if (arduboy.pressed(down_btn)) {
    //   player.animation.vel.x = -walkSpeed * PIXEL_SCALE;
    // } else if (arduboy.notPressed(up_btn | down_btn)) {
    //   player.animation.vel.x = 0;
    // }
  }

  if (arduboy.justPressed(A_BUTTON)) {
    if (player.state != PlayerState::grounded) {
      shootTimer = 0;
      Bullet::shoot();
    } else {
      Player::jump();
      triggerReleased = false;
    }
  } else if (arduboy.pressed(A_BUTTON) && player.state != PlayerState::grounded) {
    if (triggerReleased) Bullet::shoot();
  } else if (arduboy.justReleased(A_BUTTON)) {
    triggerReleased = true;
    shootTimer = FIRE_RATE;
  }


  //debug & tuning
  if (arduboy.justPressed(B_BUTTON)) {
    // Level::clearBlocks();
    // Player::flicker();
    Particles::spawnExplosion(player.animation.pos);
  }

  if (arduboy.justPressed(up_btn)) {
  } else if (arduboy.justPressed(down_btn)) {
  }
}

void update() {
  Player::update();
  Bullet::update();
  Enemies::update();
  Particles::update();
  HUD::update();
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
  Particles::draw();
  HUD::draw();
}

}
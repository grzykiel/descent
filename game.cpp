#include "game.h"

int8_t deathTimer;

namespace Game {
void loop() {
  if (gameState != STATE_DEATH) input();
  update();
  draw();
}

void init() {
  arduboy.setFrameRate(FPS);
  Level::init();
  Player::init();
  Enemies::init();
  Particles::init();
  Bullet::init();
  Powerups::init();
  HUD::init();
  Sound::init();
  Score::init();
}

void input() {
  if (arduboy.pressed(left_btn)) {
    Player::run(Direction::left);
  } else if (arduboy.pressed(right_btn)) {
    Player::run(Direction::right);
  } else if (arduboy.notPressed(left_btn | right_btn)) {
    Player::stop();
  }

  if (arduboy.justPressed(A_BUTTON | up_btn | down_btn)) {
    if (player.state != PlayerState::grounded) {
      shootTimer = 0;
      Bullet::shoot();
    } else {
      Player::jump();
      triggerReleased = false;
    }
  } else if (arduboy.anyPressed(A_BUTTON | up_btn | down_btn) && player.state != PlayerState::grounded && activeGun != GunType::laser && activeGun != GunType::shot) {
    if (triggerReleased) Bullet::shoot();
  } else if (arduboy.justReleased(A_BUTTON) || arduboy.justReleased(up_btn) || arduboy.justReleased(down_btn)) {
    triggerReleased = true;
    shootTimer = fireRate;
  }

  if (arduboy.justPressed(B_BUTTON)) {
    gameState = STATE_PAUSED;
  }
}

void update() {
  if (gameState == STATE_DEATH) {
    deathTimer--;
    if (deathTimer == 0) {
      gameState = STATE_GAMEOVER;
      arduboy.setFrameRate(FPS);
    }
    return;
  }
  Player::update();
  Bullet::update();
  Enemies::update();
  Particles::update();
  HUD::update();
  Level::update();
  updateCamera();
  Sound::update();
}

void updateCamera() {
  cameraOffset = Utils::trim(player.animation.pos.x / PIXEL_SCALE - SCREENMID, 0, MAPHEIGHT * BLOCKSIZE - SCREENTOP);
}

void draw() {
  Player::draw();
  Level::draw();
  Bullet::draw();
  Enemies::draw();
  Particles::draw();
  Powerups::draw();
  HUD::draw();
}

void onDie() {
  Sound::playGameover();
  arduboy.setFrameRate(15);
  gameState = STATE_DEATH;
  deathTimer = 45;
}

}
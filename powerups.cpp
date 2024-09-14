#include "powerups.h"

powerup_t powerup[N_POWERUPS];

const uint8_t powerupSpawnProb[] PROGMEM = { 10, 10, 10, 10, 10, 10, 10 };  

namespace Powerups {
void init() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    powerup[i].active = false;
    powerup[i].prob = (uint8_t) pgm_read_word(&powerupSpawnProb[i]);
  }
}

void draw() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    if (powerup[i].active) {
      sprites.drawSelfMasked(powerup[i].pos.x - cameraOffset, powerup[i].pos.y, powerupSprite, i);
    }
  }
}

void onShiftMap() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    if (!powerup[i].active) continue;

    if (powerup[i].pos.x < OFFSCREEN) {
      Level::shiftPos(&powerup[i].pos);
    } else {
      powerup[i].active = false;
    }
  }
}

void spawn(uint8_t type, uint16_t x, int16_t y) {
  if (!random(0, powerup[type].prob)) {
    powerup[type].active = true;
    powerup[type].pos.x = x;
    powerup[type].pos.y = y;
  } else {
    powerup[type].active = false;
  }
}

void collect(uint8_t type) {
  powerup[type].active = false;
  if (type == HEART) {
    Player::onPickupHeart();
    Particles::activateRecharge();  // TODO powerup animation
    HUD::onRecharge();              // TODO show only hearts
  }
}


}
#include "powerups.h"

powerup_t powerup[N_POWERUPS];

const uint8_t powerupSpawnProb[] = { 2, 10, 10, 10, 10, 10, 10 };  //TODO PROGMEM

namespace Powerups {
void init() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    powerup[i].active = false;
    powerup[i].prob = powerupSpawnProb[i];
  }
}

void draw() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    if (powerup[i].active) {
      sprites.drawSelfMasked(powerup[i].pos.x / PIXEL_SCALE - cameraOffset, powerup[i].pos.y / PIXEL_SCALE, powerupSprite, i);
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
    powerup[type].pos.x = x * PIXEL_SCALE;
    powerup[type].pos.y = y;
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
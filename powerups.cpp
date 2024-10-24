#include "powerups.h"

powerup_t powerup[N_POWERUPS];

uint8_t heartProb;
uint8_t upgradeProb;

namespace Powerups {
void init() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    powerup[i].active = false;
  }
  heartProb = HEART_PROB_INIT;
  upgradeProb = UPGRADE_PROB_INIT;
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
  bool activate = false;

  if (type == HEART) {
    if (!random(0, heartProb)) {
      activate = true;
      heartProb = min(++heartProb, PROB_MAX);
    }
  } else if (!random(0, upgradeProb)) {
    type = random(1, 3);
    activate = true;
    upgradeProb = min(++upgradeProb, PROB_MAX);
  }

  if (activate) {
    powerup[type].active = true;
    powerup[type].pos.x = x;
    powerup[type].pos.y = y;
  }
}

void spawnHeart(uint16_t x, uint8_t y) {
  if (!random(0, heartProb)) {
    powerup[HEART].active = true;
    powerup[HEART].pos.x = x;
    powerup[HEART].pos.y = y;
    heartProb = min(++heartProb, PROB_MAX);
  }
}

void spawnUpgrade(uint16_t x, uint8_t y) {
  if (!random(0, upgradeProb)) {
    uint8_t ug = random(1, 6);
    powerup[ug].active = true;
    powerup[ug].pos.x = x;
    powerup[ug].pos.y = y;
    upgradeProb = min(upgradeProb + 1, PROB_MAX);
  }
}

void collect(uint8_t type) {
  powerup[type].active = false;
  Particles::activateRecharge();  // TODO powerup animation
  HUD::onRecharge();
}



}
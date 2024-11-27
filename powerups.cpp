#include "powerups.h"

powerup_t powerup[N_POWERUPS];

uint8_t heartProb;
uint8_t upgradeProb;
uint8_t nextHeart;
uint8_t nextUpgrade;

namespace Powerups {
void init() {
  for (uint8_t i = 0; i < N_POWERUPS; i++) {
    powerup[i].active = false;
  }
  heartProb = HEART_PROB_INIT;
  upgradeProb = UPGRADE_PROB_INIT;
  nextHeart = HEART_PROB_INIT + random(0, heartProb);
  nextUpgrade = UPGRADE_PROB_INIT + random(0, nextUpgrade);
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


void spawnHeart(uint16_t x, uint8_t y) {
  nextHeart--;
  if (nextHeart == 0) {
    powerup[HEART].active = true;
    powerup[HEART].pos.x = x;
    powerup[HEART].pos.y = y;
    heartProb = min(++heartProb, PROB_MAX);
    nextHeart = min(HEART_PROB_INIT + random(0, heartProb), PROB_MAX);
  }
}

void spawnUpgrade(uint16_t x, uint8_t y) {
  nextUpgrade--;
  if (nextUpgrade == 0) {
    uint8_t ug = random(1, 6);
    powerup[ug].active = true;
    powerup[ug].pos.x = x;
    powerup[ug].pos.y = y;
    upgradeProb = min(++upgradeProb, PROB_MAX);
    nextUpgrade = (UPGRADE_PROB_INIT + random(0, upgradeProb), PROB_MAX);
  }
}

void collect(uint8_t type) {
  powerup[type].active = false;
  Particles::activateRecharge();  // TODO powerup animation
}



}
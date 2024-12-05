#include "powerups.h"

upgrade_t upgrade[2];

uint8_t heartProb;
uint8_t upgradeProb;
uint8_t nextHeart;
uint8_t nextUpgrade;

namespace Powerups {
void init() {
  for (uint8_t i = 0; i < 2; i++) {
    upgrade[i].type = INACTIVE;
  }
  heartProb = HEART_PROB_INIT;
  upgradeProb = UPGRADE_PROB_INIT;
  nextHeart = HEART_PROB_INIT + random(0, heartProb);
  nextUpgrade = UPGRADE_PROB_INIT + random(0, upgradeProb);
}

void draw() {
  for (uint8_t i = 0; i < 2; i++) {
    if (upgrade[i].type != INACTIVE) {
      sprites.drawSelfMasked(upgrade[i].pos.x - cameraOffset, upgrade[i].pos.y, Powerups::upgradeSprite, upgrade[i].type);
    }
  }
}

void onShiftMap() {
  for (uint8_t i = 0; i < 2; i++) {
    if (upgrade[i].type == INACTIVE) continue;
    if (upgrade[i].pos.x < OFFSCREEN) {
      upgrade[i].pos.x += 128;
    } else {
      upgrade[i].type = INACTIVE;
    }
  }
}

void spawnHeart(uint16_t x, uint8_t y) {
  nextHeart--;
  if (nextHeart == 0) {
    upgrade[HEALTH_UPGRADE].type = random(0, 2) ? HEART : HEART_CONTAINER;
    upgrade[HEALTH_UPGRADE].pos.x = x;
    upgrade[HEALTH_UPGRADE].pos.y = y;
    heartProb = min(heartProb + 1, PROB_MAX);
    nextHeart = min(HEART_PROB_INIT + random(0, heartProb), PROB_MAX);
  }
}

void spawnUpgrade(uint16_t x, uint8_t y) {
  nextUpgrade--;
  if (nextUpgrade == 0) {
    uint8_t ug = random(AMMO_CONTAINER, MACHINEGUN + 1);
    upgrade[WEAPON_UPGRADE].type = ug;
    upgrade[WEAPON_UPGRADE].pos.x = x;
    upgrade[WEAPON_UPGRADE].pos.y = y;
    upgradeProb = min(upgradeProb + 1, PROB_MAX);
    nextUpgrade = min(UPGRADE_PROB_INIT + random(0, upgradeProb), PROB_MAX);
  }
}

void collect(uint8_t type) {
  upgrade[type].type = INACTIVE;
  Particles::activateRecharge();
}


}
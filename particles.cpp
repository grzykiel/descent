#include "particles.h"

particle_t blockFragment[MAX_BLOCK_FRAGMENTS];
uint8_t blockTransitions[] = { 3, 6, 9 };
uint8_t blockIndex = 0;

particle_t explosion[MAX_EXPLOSIONS];
uint8_t ES = 4;
uint8_t explosionTransitions[] = {1*ES, 2*ES, 3*ES, 4*ES, 5*ES, 6*ES, 7*ES, 8*ES};//{ 6, 12, 18, 24, 30, 36, 42, 48 };
uint8_t explosionIndex = 0;

particle_t rechargeAnimation;
uint8_t rechargeTransitions[] = { 1, 2, 3, 4, 5, 6, 7 };

particle_t smoke;
uint8_t smokeTransitions[] = { 5, 10, 15, 20};

namespace Particles {
void init() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    blockFragment[i].sprite = Particles::blockFragmentsSprite;
    blockFragment[i].transitions = blockTransitions;
    blockFragment[i].active = false;
    blockFragment[i].last = 2;
    initBlockFragment(i);
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    explosion[i].sprite = Particles::explosionSprite;
    explosion[i].transitions = explosionTransitions;
    explosion[i].active = false;
    explosion[i].last = 7;
    initExplosion(i);
  }

  rechargeAnimation.sprite = Particles::recharge;
  rechargeAnimation.transitions = rechargeTransitions;
  rechargeAnimation.active = false;
  rechargeAnimation.last = 6;
  initRecharge();

  smoke.sprite = Particles::smokeSprite;
  smoke.transitions = smokeTransitions;
  smoke.active = false;
  smoke.last = 3;
  initSmoke();
}

void initBlockFragment(uint8_t i) {
  blockFragment[i].t = 0;
  blockFragment[i].frame = 0;
}

void spawnBlockFragment(uint16_t i, uint8_t j) {
  initBlockFragment(blockIndex);
  blockFragment[blockIndex].pos.x = (MAPHEIGHT - i - 1) * 8 - 4;
  blockFragment[blockIndex].pos.y = j * 8 - 4;
  blockFragment[blockIndex].active = true;
  blockIndex = (blockIndex + 1) % MAX_BLOCK_FRAGMENTS;
}

void initExplosion(uint8_t i) {
  explosion[i].t = 0;
  explosion[i].frame = 0;
}

void spawnExplosion(position_t pos) {
  initExplosion(explosionIndex);
  explosion[explosionIndex].pos.x = pos.x / PIXEL_SCALE - 4;
  explosion[explosionIndex].pos.y = pos.y / PIXEL_SCALE;
  explosion[explosionIndex].active = true;
  explosionIndex = (explosionIndex + 1) % MAX_EXPLOSIONS;
}

void initSmoke() {
  smoke.t = 0;
  smoke.frame = 0;
}

void spawnSmoke() {
  if (smoke.active) return; 
  initSmoke();
  smoke.pos.x = player.animation.pos.x / PIXEL_SCALE - 16;
  smoke.pos.y = player.animation.pos.y / PIXEL_SCALE - 4;
  smoke.active = true;
}

void initRecharge() {
  rechargeAnimation.t = 0;
  rechargeAnimation.frame = 0;
}

void activateRecharge() {
  initRecharge();
  rechargeAnimation.active = true;
}

void update() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      blockFragment[i].active = Utils::updateAnimation(&blockFragment[i]);
    }
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    if (explosion[i].active) {
      explosion[i].active = Utils::updateAnimation(&explosion[i]);
    }
  }

  if (rechargeAnimation.active) {
    rechargeAnimation.active = Utils::updateAnimation(&rechargeAnimation);
    rechargeAnimation.pos.x = player.animation.pos.x / PIXEL_SCALE;
    rechargeAnimation.pos.y = player.animation.pos.y / PIXEL_SCALE - 4;
  }

  if (smoke.active) {
    smoke.active = Utils::updateAnimation(&smoke);
  }
}

void draw() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      Sprites::drawSelfMasked(blockFragment[i].pos.x - cameraOffset, blockFragment[i].pos.y, blockFragment[i].sprite, blockFragment[i].frame);
    }
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    if (explosion[i].active) {
      Sprites::drawPlusMask(explosion[i].pos.x - cameraOffset, explosion[i].pos.y, explosion[i].sprite, explosion[i].frame);
    }
  }

  if (smoke.active) {
    Sprites::drawSelfMasked(smoke.pos.x - cameraOffset, smoke.pos.y, smoke.sprite, smoke.frame);
  }

  if (rechargeAnimation.active) {
    Sprites::drawSelfMasked(rechargeAnimation.pos.x - cameraOffset, rechargeAnimation.pos.y, rechargeAnimation.sprite, rechargeAnimation.frame);
  }

  
}

}
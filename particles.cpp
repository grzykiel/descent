#include "particles.h"

particle_t blockFragment[MAX_BLOCK_FRAGMENTS];
const uint8_t blockTransitions[] PROGMEM = { 3, 6, 9 };
uint8_t blockIndex = 0;

particle_t explosion[MAX_EXPLOSIONS];
const uint8_t explosionTransitions[] PROGMEM = { 4, 8, 12, 16, 20, 24, 28, 32 };
uint8_t explosionIndex = 0;

particle_t clink[MAX_CLINKS];
const uint8_t clinkTransitions[] PROGMEM = { 2, 4, 7, 10 };
uint8_t clinkIndex = 0;

particle_t pop[MAX_POPS];
const uint8_t popTransitions[] PROGMEM = { 2, 4, 6 };  //{ 2, 4, 6, 8, 10, 12, 14, 16 };
uint8_t popIndex = 0;

particle_t rechargeAnimation;
const uint8_t rechargeTransitions[] PROGMEM = { 4, 8, 12, 16, 20 }; //{ 1, 2, 3, 4, 5, 6, 7 };

particle_t smoke;
const uint8_t smokeTransitions[] PROGMEM = { 5, 11, 17, 23 };

namespace Particles {
void init() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    blockFragment[i].active = false;
    initBlockFragment(i);
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    explosion[i].active = false;
    initExplosion(i);
  }

  for (uint8_t i = 0; i < MAX_CLINKS; i++) {
    clink[i].active = false;
    initClink(i);
  }

  for (uint8_t i = 0; i < MAX_POPS; i++) {
    pop[i].active = false;
    initPop(i);
  }

  rechargeAnimation.active = false;
  initRecharge();

  smoke.active = false;
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

// TODO simplify (pass only x y)
void spawnExplosion(position_t pos, int8_t dx, int8_t dy) {
  initExplosion(explosionIndex);
  explosion[explosionIndex].pos.x = pos.x / PIXEL_SCALE + dx - 4;
  explosion[explosionIndex].pos.y = pos.y / PIXEL_SCALE + dy - 4;
  explosion[explosionIndex].active = true;
  explosionIndex = (explosionIndex + 1) % MAX_EXPLOSIONS;
}

void spawnExplosion(uint16_t x, uint8_t y, int8_t dx, int8_t dy) {
  initExplosion(explosionIndex);
  explosion[explosionIndex].pos.x = x + dx - 4;
  explosion[explosionIndex].pos.y = y + dy - 4;
  explosion[explosionIndex].active = true;
  explosionIndex = (explosionIndex + 1) % MAX_EXPLOSIONS;
}

void initClink(uint8_t i) {
  clink[i].t = 0;
  clink[i].frame = 0;
}

void spawnClink(uint16_t x, uint8_t y, int8_t dx, int8_t dy) {
  initClink(clinkIndex);
  clink[clinkIndex].pos.x = x + dx - 2;
  clink[clinkIndex].pos.y = y + dy;
  clink[clinkIndex].active = true;
  clinkIndex = (clinkIndex + 1) % MAX_CLINKS;
}

void spawnClink(position_t pos, int8_t dx, int8_t dy) {
  initClink(clinkIndex);
  clink[clinkIndex].pos.x = pos.x / PIXEL_SCALE + dx - 2;
  clink[clinkIndex].pos.y = pos.y / PIXEL_SCALE + dy;
  clink[clinkIndex].active = true;
  clinkIndex = (clinkIndex + 1) % MAX_CLINKS;
}

void initPop(uint8_t i) {
  pop[i].t = 0;
  pop[i].frame = 0;
}

void spawnPop(position_t pos, int8_t dx, int8_t dy) {
  initPop(popIndex);
  pop[popIndex].pos.x = pos.x / PIXEL_SCALE + dx - 8;
  pop[popIndex].pos.y = pos.y / PIXEL_SCALE + dy - 8;
  pop[popIndex].active = true;
  popIndex = (popIndex + 1) % MAX_POPS;
}

void initSmoke() {
  smoke.t = 0;
  smoke.frame = 0;
}

void spawnSmoke() {
  if (smoke.active) return;
  initSmoke();
  smoke.pos.x = player.animation.pos.x / PIXEL_SCALE - 16;  //24;
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
  if (rechargeAnimation.active) {
    rechargeAnimation.pos.x = player.animation.pos.x / PIXEL_SCALE;
    rechargeAnimation.pos.y = player.animation.pos.y / PIXEL_SCALE - 4;
  }
}

void draw() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      Sprites::drawSelfMasked(blockFragment[i].pos.x - cameraOffset, blockFragment[i].pos.y, Particles::blockFragmentsSprite, blockFragment[i].frame);
      blockFragment[i].active = Utils::updateAnimation(&blockFragment[i], blockTransitions, BLOCK_TRANSITIONS);
    }
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    if (explosion[i].active) {
      Sprites::drawPlusMask(explosion[i].pos.x - cameraOffset, explosion[i].pos.y, Particles::explosionSprite, explosion[i].frame);
      explosion[i].active = Utils::updateAnimation(&explosion[i], explosionTransitions, EXPLOSION_TRANSITIONS);
    }
  }

  for (uint8_t i = 0; i < MAX_CLINKS; i++) {
    if (clink[i].active) {
      Sprites::drawPlusMask(clink[i].pos.x - cameraOffset, clink[i].pos.y, Particles::clinkSprite, clink[i].frame);
      clink[i].active = Utils::updateAnimation(&clink[i], clinkTransitions, CLINK_TRANSITIONS);
    }
  }

  for (uint8_t i = 0; i < MAX_POPS; i++) {
    if (pop[i].active) {
      Sprites::drawSelfMasked(pop[i].pos.x - cameraOffset, pop[i].pos.y, Particles::popSprite, pop[i].frame);
      pop[i].active = Utils::updateAnimation(&pop[i], popTransitions, POP_TRANSITIONS);
    }
  }

  if (smoke.active) {
    Sprites::drawSelfMasked(smoke.pos.x - cameraOffset, smoke.pos.y, Particles::smokeSprite, smoke.frame);
    smoke.active = Utils::updateAnimation(&smoke, smokeTransitions, SMOKE_TRANSITIONS);
  }

  if (rechargeAnimation.active) {
    if (combo > 4) {
      Sprites::drawSelfMasked(rechargeAnimation.pos.x - cameraOffset, rechargeAnimation.pos.y + 2, Particles::flame, rechargeAnimation.frame);
    } else {
      Sprites::drawSelfMasked(rechargeAnimation.pos.x - cameraOffset, rechargeAnimation.pos.y, Particles::recharge, rechargeAnimation.frame);
    }
    rechargeAnimation.active = Utils::updateAnimation(&rechargeAnimation, rechargeTransitions, RECHARGE_TRANSITIONS);
  }
}

void onShiftMap() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) Level::shiftPos(&blockFragment[i].pos);
  }

  for (uint8_t i = 0; i < MAX_EXPLOSIONS; i++) {
    if (explosion[i].active) Level::shiftPos(&explosion[i].pos);
  }

  for (uint8_t i = 0; i < MAX_POPS; i++) {
    if (pop[i].active) Level::shiftPos(&pop[i].pos);
  }

  if (smoke.active) Level::shiftPos(&smoke.pos);

  if (rechargeAnimation.active) Level::shiftPos(&rechargeAnimation.pos);
}

}
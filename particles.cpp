#include "particles.h"

particle_t blockFragment[MAX_BLOCK_FRAGMENTS];
uint8_t blockTransitions[] = { 3, 6, 9 };

particle_t rechargeAnimation;
uint8_t rechargeTransitions[] = { 1, 2, 3, 4, 5, 6, 7 };

uint8_t blockIndex = 0;
// bulletImpact
// explosion
// skrrt
// playerImpact

namespace Particles {
void init() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    blockFragment[i].sprite = Particles::blockFragmentsSprite;
    blockFragment[i].transitions = blockTransitions;
    blockFragment[i].active = false;
    initBlockFragment(i);
  }

  rechargeAnimation.sprite = Particles::recharge;
  rechargeAnimation.transitions = rechargeTransitions;
  rechargeAnimation.active = false;
  rechargeAnimation.last = 6;
  initRecharge();
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

  if (rechargeAnimation.active) {
    rechargeAnimation.active = Utils::updateAnimation(&rechargeAnimation);
    rechargeAnimation.pos.x = player.animation.pos.x/PIXEL_SCALE;
    rechargeAnimation.pos.y = player.animation.pos.y/PIXEL_SCALE - 4;
  }
}



void draw() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      Sprites::drawSelfMasked(blockFragment[i].pos.x - cameraOffset, blockFragment[i].pos.y, blockFragment[i].sprite, blockFragment[i].frame);
    }
  }

  if (rechargeAnimation.active) {
    Sprites::drawSelfMasked(rechargeAnimation.pos.x - cameraOffset, rechargeAnimation.pos.y, rechargeAnimation.sprite, rechargeAnimation.frame);
  }
}

}
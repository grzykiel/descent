#include "particles.h"

particle_t blockFragment[MAX_BLOCK_FRAGMENTS];
uint8_t blockTransitions[] = { 3, 6, 9};

uint8_t blockIndex = 0;
// bulletImpact
// explosion
// skrrt
// playerImpact

namespace Particles {
void init() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    blockFragment[i].sprite = Particles::blockFragmentsSprite;
    blockFragment[i].active = false;
    blockFragment[i].t = 0;
    blockFragment[i].last = 2;
    blockFragment[i].frame = 0;
    blockFragment[i].transitions = blockTransitions;
  }
}

void update() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      blockFragment[i].active = Utils::updateAnimation(&blockFragment[i]);
    }
  }
}

void spawnBlockFragment(uint16_t i, uint8_t j) {
  blockFragment[blockIndex].active = true;
  blockFragment[blockIndex].t = 0;
  blockFragment[blockIndex].frame = 0;
  blockFragment[blockIndex].pos.x = (MAPHEIGHT - i - 1)*8 - 4;
  blockFragment[blockIndex].pos.y = j*8 - 4;
  blockIndex = (blockIndex + 1) % MAX_BLOCK_FRAGMENTS;
}

void draw() {
  for (uint8_t i = 0; i < MAX_BLOCK_FRAGMENTS; i++) {
    if (blockFragment[i].active) {
      Sprites::drawSelfMasked(blockFragment[i].pos.x - cameraOffset, blockFragment[i].pos.y, blockFragment[i].sprite, blockFragment[i].frame);
    }
  } 
  // Sprites::drawSelfMasked(64, 32, blockFragment[0].sprite, 1); 
}

}
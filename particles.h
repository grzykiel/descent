#ifndef PARTICLES_H
#define PARTICLES_H

#include "globals.h"
#include "player.h"
#include "bullet.h"

#define MAX_BLOCK_FRAGMENTS 5

extern particle_t blockFragment[MAX_BLOCK_FRAGMENTS];


namespace Particles {
  void init();
  void update();
  void draw();

  void initRecharge();
  void activateRecharge();

  void draw(particle_t);

  void initBlockFragment(uint8_t i);
  void spawnBlockFragment(uint16_t i, uint8_t j);

}

#endif
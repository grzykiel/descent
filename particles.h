#ifndef PARTICLES_H
#define PARTICLES_H

#include "globals.h"
#include "player.h"
#include "bullet.h"

#define MAX_BLOCK_FRAGMENTS 5
#define MAX_EXPLOSIONS      5
#define MAX_POPS            5
#define MAX_CLINKS          5

#define BLOCK_TRANSITIONS     2
#define EXPLOSION_TRANSITIONS 7
#define CLINK_TRANSITIONS     3
#define POP_TRANSITIONS       7
#define SMOKE_TRANSITIONS     3
#define RECHARGE_TRANSITIONS  6

namespace Particles {
void init();
void update();
void draw();

void draw(particle_t);

void initRecharge();
void activateRecharge();

void initBlockFragment(uint8_t i);
void spawnBlockFragment(uint16_t i, uint8_t j);

void initExplosion(uint8_t i);
void spawnExplosion(position_t pos);

void initClink(uint8_t i);
void spawnClink(position_t pos);

void initPop(uint8_t i);
void spawnPop(position_t pos);

void initSmoke();
void spawnSmoke();

void onShiftMap();
}

#endif
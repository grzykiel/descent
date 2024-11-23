#ifndef POWERUPS_H
#define POWERUPS_H

#include "globals.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"

#define N_POWERUPS 6

#define HEART 0
#define HEART_UPGRADE 1
#define AMMO_UPGRADE 2
#define SHOTGUN 3
#define LASER 4
#define MACHINEGUN 5

#define HEART_PROB_INIT 10
#define UPGRADE_PROB_INIT 20
#define PROB_MAX 127

extern powerup_t powerup[N_POWERUPS];

namespace Powerups {
void init();
void draw();
void onShiftMap();

void collect(uint8_t type);
void spawnHeart(uint16_t x, uint8_t y);
void spawnUpgrade(uint16_t x, uint8_t y);

}

#endif
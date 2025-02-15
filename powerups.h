#ifndef POWERUPS_H
#define POWERUPS_H

#include "globals.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"

#define N_POWERUPS 6

#define HEALTH_UPGRADE  0
#define WEAPON_UPGRADE  1


#define HEART           0
#define HEART_CONTAINER 1
#define AMMO_CONTAINER  2
#define SHOTGUN         3
#define LASER           4
#define MACHINEGUN      5
#define INACTIVE        6

#define HEART_PROB_INIT     3
#define UPGRADE_PROB_INIT   10
#define PROB_MAX            127

extern upgrade_t upgrade[2];

namespace Powerups {
void init();
void draw();
void onShiftMap();

void collect(uint8_t type);
void spawnHeart(uint16_t x, uint8_t y);
void spawnUpgrade(uint16_t x, uint8_t y);

}

#endif
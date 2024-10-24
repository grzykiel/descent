#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"

#define MAX_AMMO 20
#define AMMO_INIT 5
#define BULLET_ACCEL_INIT 26  //20
#define BULLET_V0_INIT 500    //410
#define FIRE_RATE_INIT 15
#define FIRE_RATE_MIN 5
#define BULLET_THRUST_SCALE 1

#define LASER_TIME 5
#define LASER_WIDTH_INIT 3
#define LASER_THRUST_SCALE 9//17

#define SHOT_ACCEL_INIT 5
#define SHOT_V0_INIT 96
#define N_SHOTS 3
#define SHOT_THRUST_SCALE 9//17


const uint8_t muzzleFlashTransitions[] PROGMEM = { 5 };
extern uint8_t shootTimer;
extern bool triggerReleased;

extern animation_t bullet[MAX_AMMO];
extern uint8_t bulletsRemaining;
extern uint8_t fireRate;
extern GunType activeGun;

const uint8_t bulletTransitions[] PROGMEM = { 2, 3, 5, 8, 11, 15, 20 };  //{ 1, 2, 3, 5, 8, 11, 15 };
const uint8_t shotVelocitiesX[] PROGMEM = { SHOT_V0_INIT - 20, SHOT_V0_INIT, SHOT_V0_INIT - 20 };
const int8_t shotVelocitiesY[] PROGMEM = { -SHOT_V0_INIT/2, 0, SHOT_V0_INIT/2 };

namespace Bullet {
void init();
void update();
void draw();

void shoot();
void reload();
void fireAuto();
void fireLaser();
void fireShotgun();

void initMuzzleFlash();
void drawMuzzleFlash();

void initBullets();
void updateBullets();
void updateLaser();
void collisionCheck();
void drawBullets();
void drawLaser();

void onShiftMap();

void setActiveGun(GunType newType);
void increaseCap();
}

#endif
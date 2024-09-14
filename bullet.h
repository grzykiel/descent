#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"

#define AMMO_CAP 5
#define AMMO_INIT 5
#define BULLET_ACCEL_INITIAL 26       //20
#define BULLET_V0_INITIAL 500  //410
#define FIRE_RATE_INITIAL 15
#define FIRE_RATE_MIN 5

const uint8_t muzzleFlashTransitions[] PROGMEM = { 5 };
extern uint8_t shootTimer;
extern bool triggerReleased;

extern animation_t bullet[AMMO_CAP];
extern uint8_t bulletsRemaining;
extern uint8_t fireRate;

const uint8_t bulletTransitions[] PROGMEM = {2, 3, 5, 8, 11, 15, 20}; //{ 1, 2, 3, 5, 8, 11, 15 };  //, 20};

namespace Bullet {
void init();
void update();
void draw();

void shoot();
void reload();

void initMuzzleFlash();
void drawMuzzleFlash();

void initBullets();
void updateBullets();
void collisionCheck();
void drawBullets();

void drawAmmo();

void onShiftMap();
}

#endif
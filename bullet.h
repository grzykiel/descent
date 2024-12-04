#ifndef BULLET_H
#define BULLET_H
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "game.h"
#include "levels.h"
#include "hud.h"
#include "particles.h"
#include "sound.h"

#define MAX_AMMO  20
#define AMMO_INIT 8

#define BULLET_ACCEL_INIT   26  
#define BULLET_V0           500
#define FIRE_RATE_INIT      16
#define FIRE_RATE_MIN       5
#define BULLET_THRUST_SCALE 1

#define LASER_TIME          5
#define LASER_WIDTH_INIT    2
#define LASER_THRUST_SCALE  17
#define LASER_CHARGES       2
#define SHOT_ACCEL_INIT     5
#define N_SHOTS             5
#define SHOT_CHARGES        3
#define SHOT_THRUST_SCALE   17

constexpr uint8_t muzzleFlashTransitions[] PROGMEM = { 5 };
extern uint8_t shootTimer;
extern bool triggerReleased;

extern bullet_t bullet[MAX_AMMO];
extern sprite_t bulletSprite;
extern uint8_t bulletsRemaining;
extern uint8_t fireRate;
extern GunType activeGun;

constexpr uint8_t bulletTransitions[] PROGMEM = { 2, 3, 5, 8, 11, 15, 20 }; 
constexpr int16_t shotVelocitiesX[] PROGMEM = {205, 198, 152}; 
constexpr int8_t shotVelocitiesY[] PROGMEM = {0, 53, 20}; 

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
void activateMuzzleFlash();
bool updateBulletAnimation(bullet_t *bullet);

void initBullets();
void updateBullets();
void updateLaser();
void collisionCheck();
void drawBullets();
void drawLaser();

void onEmpty();
void onShiftMap();

void setActiveGun(GunType newType);
void increaseCap();
}

#endif
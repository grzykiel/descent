#ifndef ENEMIES_H
#define ENEMIES_H 
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "bullet.h"

#define MAX_ENEMIES   5

#define BLOB_MAX_VEL  8
#define BLOB_RECOIL_VEL -96
#define BAT_VEL 16

#define BLOB_HP 3
#define BAT_HP  2
#define WORM_HP 1
#define TORTOISE_HP 1

enum class EnemyType : uint8_t {
  blob,
  hangingBat,
  bat,
  worm,
  tortoise
};

typedef struct {
  EnemyType type;
  uint8_t hp;
	animation_t animation;
} enemy_t;

extern enemy_t enemy[MAX_ENEMIES];

namespace Enemies {

  void init();
  void update();
  void draw();

  void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel);
  void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel);
  void checkBulletCollisions(enemy_t *enemy, velocity_t *nextVel);
  bool updateSprite(enemy_t *enemy);

  void spawn(EnemyType type, uint16_t x, uint8_t y);
  void wake(enemy_t *bat);
  void testWake();

  void kill(enemy_t *enemy, bool shot);
}

#endif
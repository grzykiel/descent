#ifndef ENEMIES_H
#define ENEMIES_H 
#include "globals.h"
#include "bitmaps.h"
#include "player.h"
#include "bullet.h"
#include "powerups.h"
#include "score.h"

#define MAX_ENEMIES     10

#define BLOB_MAX_VEL    8
#define BLOB_RECOIL_VEL -96
#define BAT_VEL         32
#define CRAWLER_VEL     24
#define WORM_VEL        1 //pixels moved on animation update
#define TORTOISE_VEL    2 // """

#define BLOB_HP     3
#define BAT_HP      2
#define WORM_HP     1
#define TORTOISE_HP 1
#define CRAWLER_HP  1

#define CRAWLER_UP      0
#define CRAWLER_RIGHT   1
#define CRAWLER_DOWN    2
#define CRAWLER_LEFT    3
#define CRAWLER_WIDTH   5
#define CRAWLER_HEIGHT  4

enum class EnemyType : uint8_t {
  blob,
  hangingBat,
  bat,
  worm,
  tortoise,
  crawler,
  fallingCrawler
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

  void checkBulletCollisions(enemy_t *enemy, velocity_t *nextVel);
  bool checkLaserCollisions(Rect laser);
  bool updateSprite(enemy_t *enemy);

  void checkTileCollision(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel);
  void updateCrawling(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel);  // worm & tortoise
  void updateFlying(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel);
  void updateCrawler(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel);   // wall crawler
  bool ledgeDetect(animation_t animation);
  void checkCrawlerCollision(enemy_t *enemy, position_t *nextPos, velocity_t *nextVel);

  void spawn(EnemyType type, uint16_t x, uint8_t y);
  void wake(enemy_t *bat);
  void setCrawlerDirection(enemy_t *crawler, Direction dir);
  void crawlerFall(enemy_t *crawler, velocity_t *nextVel);
  void crawlerLand(enemy_t *crawler, velocity_t *nextVel);

  void kill(enemy_t *enemy, bool shot);

  void onShiftMap();
}

#endif
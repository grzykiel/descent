#include "globals.h"
#include "bitmaps.h"
#include "player.h"

#define BLOB_MAX_VEL  8
#define MAX_ENEMIES   1

#define BLOB 0

typedef struct {
  char type;
  uint8_t hp;
	animation_t animation;
} enemy_t;

extern enemy_t enemyBlob;

namespace Enemies {

  void init();
  void update();
  void draw();

  void updatePosition(enemy_t enemy, position_t *nextPos, velocity_t *nextVel);
  void checkCollisions(enemy_t enemy, position_t *nextPos, velocity_t *nextVel);
  void updateSprite(enemy_t enemy);

  
}
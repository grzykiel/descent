#include "globals.h"
#include "bitmaps.h"
#include "player.h"

#define BLOB_MAX_VEL  8
#define MAX_ENEMIES   1

typedef struct {
	int8_t vx;
	int8_t vy;
	
	animation_t animation;
} enemy_t;

extern enemy_t enemyBlob;

namespace Enemies {

  void init();
  void update();
  void draw();

  void updatePositions(); //TODO remove
  vector_t updatePositions(enemy_t enemy);
  void updateSprites();

  void checkCollisions();
}
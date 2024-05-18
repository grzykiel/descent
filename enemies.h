#include "globals.h"
#include "bitmaps.h"
#include "player.h"

#define BLOB_MAX_VEL  8

typedef struct {
	int8_t vx;
	int8_t vy;
	
	animation_t animation;
} enemy_t;


  /*animation_t animation = {
    .active = false,
    .frame = 0,
    .t = 0,
    .x = SCREENMID + 128,
    .y = 28,
    .sprite = {
      .sprite = Player::runRightSprite,
      .last = null, // change for jumping
      .transitions = null, // change for jumping
      .dx = 0,
      .dy = 1,
      .w = 6,
      .h = 8
    }
  }*/

extern enemy_t enemyBlob;

namespace Enemies {

  void init();
  void update();
  void draw();

  void updatePositions();
  void updateSprites();

}
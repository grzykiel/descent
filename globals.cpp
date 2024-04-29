#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

// uint8_t gameState = STATE_SANDBOX; 
uint8_t gameState = STATE_GAME;

// uint8_t movementMode = TOPDOWN;
uint8_t movementMode = PLATFORM;

int16_t cameraOffset = 0;

namespace Utils {

int trim(int p, int l, int h) {
  return min(h, max(p, l));
}

window_t getCollisionWindow(uint16_t x, uint8_t y) {
  window_t wd;
  //TODO use trim()
  wd.yMin = max(floor(y / BLOCKSIZE) - 1, 0);
  wd.yMax = min(ceil(y / BLOCKSIZE) + 1, MAPWIDTH - 1);

  wd.xMin = ceil(x / (1.0f * BLOCKSIZE)) + 1;
  wd.xMax = floor(x / (1.0f * BLOCKSIZE)) - 1;
  wd.xMin = max(MAPHEIGHT - 1 - wd.xMin, 0);
  wd.xMax = min(MAPHEIGHT - 1 - wd.xMax, MAPHEIGHT - 1);

  return wd;
}

bool collides(animation_t anim, Rect block) {
  Rect spriteRect = Rect(anim.x + anim.sprite->dx, anim.y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  return (arduboy.collide(spriteRect, block));
}

collision_t collisionCorrect(animation_t anim, vector_t *next, Rect collider) {
  collision_t type = {NONE, NONE};

  /*uint8_t y = min(next->y, anim.y);
  uint8_t w = abs(next->y - anim.y);
  Rect rect = Rect(anim.x + anim.sprite->dx, y + anim.sprite->dy, anim.sprite->h, w +anim.sprite->w);*/

  Rect rect = Rect(anim.x + anim.sprite->dx, next->y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.y < rect.y) {
      type.h = LEFT;
      next->y = collider.y + collider.height - anim.sprite->dy;
    } else if (rect.y < collider.y) {
      type.h = RIGHT;
      next->y = collider.y - anim.sprite->w - anim.sprite->dy;
    }
  }

  /*uint8_t x = min(next->x, anim.x);
  uint8_t h = abs(next->x - anim.x);
  rect = Rect(x + anim.sprite->dx, anim.y + anim.sprite->dy, h + anim.sprite->h, anim.sprite->w);*/

  rect = Rect(next->x + anim.sprite->dx, anim.y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < anim.x) {
      type.v = BOTTOM;
      next->x = collider.x + collider.width - anim.sprite->dx;
    } else if (anim.x < collider.x) {
      type.v = TOP;
      next->x = collider.x - anim.sprite->h - anim.sprite->dx;
    }
  }

  return type;
}

bool updateAnimation(animation_t *anim) {
  anim->t++;
  if (anim->t == anim->sprite->transitions[anim->frame]) {
    if (anim->frame < anim->sprite->last) {
      anim->frame++;
    } else {
      return false;
    }
  }
  return true;
}


}
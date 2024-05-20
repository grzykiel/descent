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

window_t getCollisionWindow(position_t pos) {
  return getCollisionWindow(pos.x, pos.y);
}

window_t getCollisionWindow(uint16_t x, int16_t y) {
  window_t wd;
  //TODO use trim()
  wd.yMin = max(floor(y/PIXEL_SCALE / BLOCKSIZE) - 1, 0);
  wd.yMax = min(ceil(y/PIXEL_SCALE / BLOCKSIZE) + 1, MAPWIDTH - 1);

  wd.xMin = ceil(x / (1.0f * BLOCKSIZE)) + 1;
  wd.xMax = floor(x / (1.0f * BLOCKSIZE)) - 1;
  wd.xMin = max(MAPHEIGHT - 1 - wd.xMin, 0);
  wd.xMax = min(MAPHEIGHT - 1 - wd.xMax, MAPHEIGHT - 1);

  return wd;
}

bool collides(animation_t anim, Rect block) {
  Rect spriteRect = Rect(anim.pos.x + anim.sprite->dx, anim.pos.y + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  return (arduboy.collide(spriteRect, block));
}

collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider) {
  collision_t type = {NONE, NONE};

  /*uint8_t y = min(next->y, anim.pos.y);
  uint8_t w = abs(next->y - anim.pos.y);
  Rect rect = Rect(anim.pos.x + anim.sprite->dx, y + anim.sprite->dy, anim.sprite->h, w +anim.sprite->w);*/

  Rect rect = Rect(anim.pos.x + anim.sprite->dx, next->y/PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);

  if (arduboy.collide(rect, collider)) {
    if (collider.y < rect.y) {
      type.h = LEFT;
      next->y = (collider.y + collider.height - anim.sprite->dy)*PIXEL_SCALE;
    } else if (rect.y < collider.y) {
      type.h = RIGHT;
      next->y = (collider.y - anim.sprite->w - anim.sprite->dy)*PIXEL_SCALE;
    }
  }

  /*uint8_t x = min(next->x, anim.pos.x);
  uint8_t h = abs(next->x - anim.pos.x);
  rect = Rect(x + anim.sprite->dx, anim.pos.y + anim.sprite->dy, h + anim.sprite->h, anim.sprite->w);*/

  rect = Rect(next->x + anim.sprite->dx, anim.pos.y/PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < rect.x) {
      type.v = BOTTOM;
      next->x = collider.x + collider.width - anim.sprite->dx;
    } else if (rect.x < collider.x) {
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


int sign(int x) {
  return (x > 0) - (x < 0);
}

void println(char *str) {
  arduboy.print(str);
  arduboy.print("\n");
}

void println(int pr_int) {
  arduboy.print(pr_int);
  arduboy.print("\n");
}

void println(uint16_t pr_int) {
  arduboy.print(pr_int);
  arduboy.print("\n");
}

void println(uint8_t pr_int) {
  arduboy.print(pr_int);
  arduboy.print("\n");
}



}
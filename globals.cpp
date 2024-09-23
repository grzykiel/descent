#include "globals.h"

Arduboy2Base arduboy;
Sprites sprites;

uint8_t gameState = STATE_MENU;

int16_t cameraOffset = 0;

namespace Utils {

int trim(int p, int l, int h) {
  return min(h, max(p, l));
}

window_t getCollisionWindow(position_t pos) {
  return getCollisionWindow(pos.x / PIXEL_SCALE, pos.y / PIXEL_SCALE);
}

window_t getCollisionWindow(uint16_t x, int16_t y) {
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
  Rect spriteRect = Rect(anim.pos.x / PIXEL_SCALE + anim.sprite->dx, anim.pos.y / PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  // arduboy.drawRect(anim.pos.x/PIXEL_SCALE + anim.sprite->dx - cameraOffset, anim.pos.y/PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  return (arduboy.collide(spriteRect, block));
}

bool collides(animation_t anim1, animation_t anim2) {
  Rect rect1 = Rect(anim1.pos.x / PIXEL_SCALE + anim1.sprite->dx, anim1.pos.y / PIXEL_SCALE + anim1.sprite->dy, anim1.sprite->h, anim1.sprite->w);
  Rect rect2 = Rect(anim2.pos.x / PIXEL_SCALE + anim2.sprite->dx, anim2.pos.y / PIXEL_SCALE + anim2.sprite->dy, anim2.sprite->h, anim2.sprite->w);
  return (arduboy.collide(rect1, rect2));
}

collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider, bool horizontal, bool vertical) {
  collision_t type = { NONE, NONE };

  // arduboy.drawRect(collider.x - cameraOffset, collider.y, collider.width, collider.height);

  Rect rect = Rect(anim.pos.x / PIXEL_SCALE + anim.sprite->dx, next->y / PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  // arduboy.fillRect(rect.x - cameraOffset, rect.y, rect.width, rect.height);
  if (arduboy.collide(rect, collider)) {
    if (collider.y < anim.pos.y / PIXEL_SCALE + anim.sprite->dy) {
      type.h = LEFT;
      if (horizontal) next->y = (collider.y + collider.height - anim.sprite->dy) * PIXEL_SCALE;
    } else if (anim.pos.y / PIXEL_SCALE + anim.sprite->dy < collider.y) {
      type.h = RIGHT;
      if (horizontal) next->y = (collider.y - anim.sprite->w - anim.sprite->dy) * PIXEL_SCALE;
    }
  }

  rect = Rect(next->x / PIXEL_SCALE + anim.sprite->dx, anim.pos.y / PIXEL_SCALE + anim.sprite->dy, anim.sprite->h, anim.sprite->w);
  // arduboy.fillRect(rect.x - cameraOffset, rect.y, rect.width, rect.height);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < anim.pos.x / PIXEL_SCALE + anim.sprite->dx) {
      type.v = BOTTOM;
      if (vertical) next->x = (collider.x + collider.width - anim.sprite->dx) * PIXEL_SCALE;
    } else if (anim.pos.x / PIXEL_SCALE + anim.sprite->dx < collider.x) {
      type.v = TOP;
      if (vertical) next->x = (collider.x - anim.sprite->h - anim.sprite->dx) * PIXEL_SCALE;
    }
  }

  return type;
}

collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider) {
  return collisionCorrect(anim, next, collider, true, true);
}

bool updateAnimation(animation_t *anim) {
  anim->t++;
  if (anim->t == (uint8_t) pgm_read_word(&anim->sprite->transitions[anim->frame])) {
    if (anim->frame < anim->sprite->last) {
      anim->frame++;
    } else {
      return false;
    }
  }
  return true;
}

bool updateAnimation(particle_t *particle, uint8_t *transitions, uint8_t last) {
  particle->t++;
  if (particle->t == (uint8_t) pgm_read_word(&transitions[particle->frame])) {
    if (particle->frame < last) { 
      particle->frame++;
    } else {
      return false;
    }
  }
  return true;
}

bool flickering(animation_t *anim) {
  return flickering(&anim->iframe);
}

bool flickering(int8_t *f) {
  if (*f == 0) return false;
  if (*f > 0) {
    (*f)--;
  } else if (*f < 0) {
    (*f)++;
  }

  if (abs(*f) % FLICKER_DURATION == 0) {
    *f *= -1;
  }

  return (*f < 0);
}

int sign(int x) {
  return (x > 0) - (x < 0);
}



}
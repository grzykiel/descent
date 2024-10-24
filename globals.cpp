#include "globals.h"

Arduboy2Base arduboy;
Sprites sprites;

uint8_t gameState = STATE_MENU;

int16_t cameraOffset = 0;

uint8_t settings = 0xFF; // sound | top display

uint16_t score;

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
  Rect spriteRect = Rect(anim.pos.x / PIXEL_SCALE + ((anim.sprite->offset & 0xF0) >> 4), anim.pos.y / PIXEL_SCALE + (anim.sprite->offset & 0x0F), anim.sprite->dim & 0x0F, (anim.sprite->dim & 0xF0) >> 4);
  // arduboy.drawRect(anim.pos.x/PIXEL_SCALE + anim.sprite->dx - cameraOffset, anim.pos.y/PIXEL_SCALE + (anim.sprite->offset & 0x0F), anim.sprite->h, anim.sprite->w);
  return (arduboy.collide(spriteRect, block));
}

bool collides(animation_t anim1, animation_t anim2) {
  Rect rect1 = Rect(anim1.pos.x / PIXEL_SCALE + ((anim1.sprite->offset & 0xF0) >> 4), anim1.pos.y / PIXEL_SCALE + (anim1.sprite->offset & 0x0F), anim1.sprite->dim & 0x0F, (anim1.sprite->dim & 0xF0) >> 4);
  Rect rect2 = Rect(anim2.pos.x / PIXEL_SCALE + ((anim2.sprite->offset & 0xF0) >> 4), anim2.pos.y / PIXEL_SCALE + (anim2.sprite->offset & 0x0F), anim2.sprite->dim & 0x0F, (anim2.sprite->dim & 0xF0) >> 4);
  return (arduboy.collide(rect1, rect2));
}

collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider, bool horizontal, bool vertical) {
  collision_t type = { NONE, NONE };

  // arduboy.drawRect(collider.x - cameraOffset, collider.y, collider.width, collider.height);

  Rect rect = Rect(anim.pos.x / PIXEL_SCALE + ((anim.sprite->offset & 0xF0) >> 4), next->y / PIXEL_SCALE + (anim.sprite->offset & 0x0F), anim.sprite->dim & 0x0F, (anim.sprite->dim & 0xF0) >> 4);
  // arduboy.fillRect(rect.x - cameraOffset, rect.y, rect.width, rect.height);
  if (arduboy.collide(rect, collider)) {
    if (collider.y < anim.pos.y / PIXEL_SCALE + (anim.sprite->offset & 0x0F)) {
      type.h = LEFT;
      if (horizontal) next->y = (collider.y + collider.height - (anim.sprite->offset & 0x0F)) * PIXEL_SCALE;
    } else if (anim.pos.y / PIXEL_SCALE + (anim.sprite->offset & 0x0F) < collider.y) {
      type.h = RIGHT;
      if (horizontal) next->y = (collider.y - ((anim.sprite->dim & 0xF0) >> 4) - (anim.sprite->offset & 0x0F)) * PIXEL_SCALE;
    }
  }

  rect = Rect(next->x / PIXEL_SCALE + ((anim.sprite->offset & 0xF0) >> 4), anim.pos.y / PIXEL_SCALE + (anim.sprite->offset & 0x0F), anim.sprite->dim & 0x0F, (anim.sprite->dim & 0xF0) >> 4);
  // arduboy.fillRect(rect.x - cameraOffset, rect.y, rect.width, rect.height);
  if (arduboy.collide(rect, collider)) {
    if (collider.x < anim.pos.x / PIXEL_SCALE + ((anim.sprite->offset & 0xF0) >> 4)) {
      type.v = BOTTOM;
      if (vertical) next->x = (collider.x + collider.width - ((anim.sprite->offset & 0xF0) >> 4)) * PIXEL_SCALE;
    } else if (anim.pos.x / PIXEL_SCALE + ((anim.sprite->offset & 0xF0) >> 4) < collider.x) {
      type.v = TOP;
      if (vertical) next->x = (collider.x - (anim.sprite->dim & 0x0F) - ((anim.sprite->offset & 0xF0) >> 4)) * PIXEL_SCALE;
    }
  }

  return type;
}

collision_t collisionCorrect(animation_t anim, position_t *next, Rect collider) {
  return collisionCorrect(anim, next, collider, true, true);
}

bool updateAnimation(animation_t *anim) {
  anim->t++;
  if (anim->t == (uint8_t)pgm_read_word(&anim->sprite->transitions[anim->frame])) {
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
  if (particle->t == (uint8_t)pgm_read_word(&transitions[particle->frame])) {
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

// x y n length font
void printNum(uint8_t x, uint8_t y, uint16_t n, uint8_t length) {
  y += (length - 1) * 4;
  for (uint8_t i = 0; i < length; i++) {
    Sprites::drawSelfMasked(x, y, Fonts::font_4x4, n % 10);
    n -= n % 10;
    n /= 10;
    y -= 4;
  }
}

void printText(uint8_t x, uint8_t y, uint8_t *text, uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    Sprites::drawSelfMasked(x, y, Fonts::font_4x4, text[i]);
    y+= 5;
  }
}

}
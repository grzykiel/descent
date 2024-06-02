#include "hud.h"

hud_t damageCounter = {
  HUD::minusOne,
  0,
  60,
  0,
  0
};

namespace HUD {

void update() {
  if (damageCounter.t > 0) {
    if (damageCounter.t > 43) {
     damageCounter.pos.x += 64; //+ round((120-damageCounter.t)/60)*8*PIXEL_SCALE;
     Utils::println(damageCounter.pos.x);
     damageCounter.pos.y = player.animation.pos.y; 
    }
    damageCounter.t--;
  }
}

void draw() {
  draw(damageCounter, 0);
}

void onDamaged() {
  damageCounter.pos = player.animation.pos;
  damageCounter.t = damageCounter.displayDuration;
}

void draw(hud_t hud, uint8_t frame) {

  if (damageCounter.t > 0) {
    sprites.drawSelfMasked(damageCounter.pos.x/PIXEL_SCALE - cameraOffset, damageCounter.pos.y/PIXEL_SCALE, damageCounter.sprite, frame);
  }
}
}
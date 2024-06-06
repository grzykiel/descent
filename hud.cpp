#include "hud.h"

hud_t damageCounter = {
  HUD::minusOne,
  0,
  0,

};

hud_t ammoCounter = {
  HUD::ammo,
  0,
  0,
};

namespace HUD {

void update() {
  if (damageCounter.t > 0) {
    if (damageCounter.t > 50) {
      damageCounter.pos.x += 128;
      damageCounter.pos.y = player.animation.pos.y;
    }
    damageCounter.t--;
  }

  if (bulletsRemaining > 0 && ammoCounter.t > 0) {
    ammoCounter.t--;
    if (ammoCounter.t > 30 || ammoCounter.f == 0) {
      ammoCounter.pos.x = player.animation.pos.x + 8 * PIXEL_SCALE;
      ammoCounter.pos.y = player.animation.pos.y - 8 * PIXEL_SCALE;
    }
  } else {
    if (ammoCounter.t > 0) {
      ammoCounter.t--;
      if (!Utils::flickering(&ammoCounter.f)) {
        draw(ammoCounter, 0);
      }
    }
  }
}


void draw() {
  if (damageCounter.t > 0) {
    draw(damageCounter, 0);
  }
  if (ammoCounter.t > 0) {
    draw(ammoCounter, bulletsRemaining);
  }
}

void onDamaged() {
  damageCounter.pos = player.animation.pos;
  damageCounter.t = 60;  // TODO #define
}

void onShoot() {
  if (bulletsRemaining == 0) {
    ammoCounter.t = 60;
    ammoCounter.f = 30;
  } else {
    ammoCounter.t = 60;
    ammoCounter.f = 0;
  }
}


void draw(hud_t hud, uint8_t frame) {
  sprites.drawSelfMasked(hud.pos.x / PIXEL_SCALE - cameraOffset, hud.pos.y / PIXEL_SCALE, hud.sprite, frame);
}
}
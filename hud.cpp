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

hud_t HP = {
  HUD::hp,
  0,
  0,
};

namespace HUD {

void update() {
  if (damageCounter.t > 0) {
    if (damageCounter.t > DAMAGE_COUNTER_FRAMES) {
      damageCounter.pos.x += 128;
      damageCounter.pos.y = player.animation.pos.y;
    }
    damageCounter.t--;
  }

  if (bulletsRemaining > 0 && ammoCounter.t > 0) {
    ammoCounter.t--;
    if (ammoCounter.t > AMMO_COUNTER_IFRAMES || ammoCounter.f == 0) {
      ammoCounter.pos.x = player.animation.pos.x + 9 * PIXEL_SCALE;
      ammoCounter.pos.y = player.animation.pos.y - 8 * PIXEL_SCALE;

      HP.pos.x = ammoCounter.pos.x + 6*PIXEL_SCALE;
      HP.pos.y = ammoCounter.pos.y;
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
    draw(HP, player.hp);
  }
}

void onDamaged() {
  damageCounter.pos = player.animation.pos;
  damageCounter.t = 60; //DAMAGE_COUNTER_FRAMES;
}

void onRecharge() {
  ammoCounter.f = 0;
  ammoCounter.t = AMMO_COUNTER_FRAMES;
}

void onShoot() {
  ammoCounter.t = AMMO_COUNTER_FRAMES;
  if (bulletsRemaining == 0) {
    ammoCounter.f = AMMO_COUNTER_IFRAMES;
  } else {
    ammoCounter.f = 0;
  }
}


void draw(hud_t hud, uint8_t frame) {
  sprites.drawSelfMasked(hud.pos.x / PIXEL_SCALE - cameraOffset, hud.pos.y / PIXEL_SCALE, hud.sprite, frame);
}

void onShiftMap() {
  if (damageCounter.t > 0) {
    Level::shiftPos(&damageCounter.pos);
  }

  if (ammoCounter.t > 0) {
    Level::shiftPos(&ammoCounter.pos);
    Level::shiftPos(&HP.pos);
  }
}
}
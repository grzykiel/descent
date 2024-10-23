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

void init() {
  damageCounter.t = 0;
  damageCounter.f = 0;
  ammoCounter.t = 0;
  ammoCounter.f = 0;
  HP.t = 0;
  HP.f = 0;
}

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

      HP.pos.x = ammoCounter.pos.x + 6 * PIXEL_SCALE;
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
    if (bulletsRemaining > 9) {
      Utils::printNum(ammoCounter.pos.x/PIXEL_SCALE - cameraOffset, ammoCounter.pos.y/PIXEL_SCALE + 6, bulletsRemaining, 2);
      Sprites::drawSelfMasked(ammoCounter.pos.x/PIXEL_SCALE - cameraOffset, ammoCounter.pos.y/PIXEL_SCALE + 15, Fonts::font_4x4, 37);
    } else {
      draw(ammoCounter, bulletsRemaining);
    }
    draw(HP, player.hp);
  }

  drawTop();
}

void drawTop() {
  arduboy.fillRect(122, 0, 6, 64, 0);

  if (player.hp > 3) {
    Utils::printNum(123, 1, player.hp, 1);
    Sprites::drawSelfMasked(123, -5, HUD::hp, 1);
  } else {
    Sprites::drawSelfMasked(123, 3 * player.hp - 12, HUD::hp, player.hp);
  }

  if (bulletsRemaining > 9) {
    Utils::printNum(123, 45, bulletsRemaining, 2);
    Sprites::drawSelfMasked(123, 42, HUD::ammo, 1);
  } else if (bulletsRemaining > 0) {
    Sprites::drawSelfMasked(123, 33 + bulletsRemaining, HUD::ammo, bulletsRemaining);
  }
}

void onDamaged() {
  damageCounter.pos = player.animation.pos;
  damageCounter.t = 60;  //DAMAGE_COUNTER_FRAMES;
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
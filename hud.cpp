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

uint8_t comboTimer;

namespace HUD {

void init() {
  damageCounter.t = 0;
  damageCounter.f = 0;
  ammoCounter.t = 0;
  ammoCounter.f = 0;
  HP.t = 0;
  HP.f = 0;

  comboTimer = 0;
}

void update() {

  if (damageCounter.t > 0) {
    damageCounter.t--;
    if (damageCounter.t > 50) {
      damageCounter.pos.x += 128;
      damageCounter.pos.y = player.animation.pos.y;
    }
  }

  if (settings & 0x0F) return;

  if (HP.t > 0) {
    update(&HP);
  } else if (bulletsRemaining > 0 && ammoCounter.t > 0) {
    update(&ammoCounter);
  } else {
    if (ammoCounter.t > 0) {
      ammoCounter.t--;
      if (!Utils::flickering(&ammoCounter.f)) {
        draw(ammoCounter, 0);
      }
    }
  }
}

void update(hud_t *hud) {
  hud->t--;
  if (hud->t > HUD_COUNTER_IFRAMES || hud->f == 0) {
    hud->pos.x = player.animation.pos.x + 9 * PIXEL_SCALE;
    hud->pos.y = player.animation.pos.y - 8 * PIXEL_SCALE;
  }
}

void draw() {

  if (damageCounter.t > 0) {
    draw(damageCounter, 0);
  }
  
  // if (Utils::flickering(&comboTimer)) {
  //   drawCombo();
  // } else if (comboTimer == 0) {
  //   Player::resetCombo();
  // }
  if (comboTimer != 0) {
    if (Utils::flickering(&comboTimer)) {
      drawCombo();
    }
    if (comboTimer == 0) {
      Player::resetCombo();
    }
  }
  
  if (settings & 0x0F) {
    drawTop();
    return;
  }

  if (HP.t > 0) {
    if (player.hp > 3) {
      Utils::printNum(HP.pos.x / PIXEL_SCALE - cameraOffset, HP.pos.y / PIXEL_SCALE + 8, player.hp, 1);
      Sprites::drawSelfMasked(HP.pos.x / PIXEL_SCALE - cameraOffset, HP.pos.y / PIXEL_SCALE + 3, HUD::hp, 1);
    } else {
      draw(HP, player.hp);
    }
  } else if (ammoCounter.t > 0) {
    if (bulletsRemaining > 9) {
      Utils::printNum(ammoCounter.pos.x / PIXEL_SCALE - cameraOffset, ammoCounter.pos.y / PIXEL_SCALE + 5, bulletsRemaining, 2);
      Sprites::drawSelfMasked(ammoCounter.pos.x / PIXEL_SCALE - cameraOffset, ammoCounter.pos.y / PIXEL_SCALE + 4, HUD::ammo, 2);
    } else {
      draw(ammoCounter, bulletsRemaining);
    }
  }
}

void drawTop() {
  arduboy.fillRect(122, 0, 6, 64, 0);

  if (player.hp > 3) {
    Utils::printNum(123, 1, player.hp, 1);
    Sprites::drawSelfMasked(123, -4, HUD::hp, 1);
  } else {
    Sprites::drawSelfMasked(123, 3 * player.hp - 12, HUD::hp, player.hp);
  }

  if (bulletsRemaining > 9) {
    Utils::printNum(123, 45, bulletsRemaining, 2);
    Sprites::drawSelfMasked(123, 44, HUD::ammo, 2);
  } else if (bulletsRemaining > 0) {
    Sprites::drawSelfMasked(123, 33 + bulletsRemaining, HUD::ammo, bulletsRemaining);
  }

  Utils::printNum(123, 20, score, 6);

  if (comboTimer == 0) drawCombo();
}

void drawCombo() {
  if (combo > 2) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, player.animation.pos.y / PIXEL_SCALE + 2, combo, 1);
  } else if (combo > 9) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, player.animation.pos.y / PIXEL_SCALE, combo, 2);
  } else if (combo > 99) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, player.animation.pos.y / PIXEL_SCALE - 3, combo, 3);
  }
}

void onComboEnd() {
  comboTimer = 60;
}

void onDamaged() {
  damageCounter.pos = player.animation.pos;
  damageCounter.t = DAMAGE_COUNTER_FRAMES + 10;

  HP.t = HUD_COUNTER_FRAMES;
  HP.f = 0;
  HP.pos = player.animation.pos;
  HP.pos.x += 9 * PIXEL_SCALE;
  ammoCounter.t = 0;
  ammoCounter.f = 0;
}

void onRecharge() {
  ammoCounter.f = 0;
  ammoCounter.t = HUD_COUNTER_FRAMES;
}

void onShoot() {
  ammoCounter.t = HUD_COUNTER_FRAMES;
  if (bulletsRemaining == 0) {
    ammoCounter.f = HUD_COUNTER_IFRAMES;
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
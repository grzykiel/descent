#include "hud.h"
uint8_t comboTimer;
hud_t empty;
hud_t damage;

namespace HUD {

void init() {
  comboTimer = 0;
  empty.t = 0;
  damage.t = 0;
}

void update() {
  if (empty.t > 0) {
    empty.t--;
  }

  if (damage.t > 0) {
    damage.t--;
    if (damage.t > DAMAGE_COUNTER_HOLD) {
      damage.pos.x += 1;
      damage.pos.y = player.animation.pos.y / PIXEL_SCALE;
    }
  }
}

void drawHud(hud_t hud, const unsigned char *sprite) {
  if ((hud.t > HUD_COUNTER_IFRAMES) || Utils::flickering(&hud.t)) {
    Sprites::drawSelfMasked(hud.pos.x - cameraOffset, hud.pos.y, sprite, 0);
  }
}

void draw() {
  drawHud(empty, HUD::ammo);
  drawHud(damage, HUD::minusOne);

  if (comboTimer != 0) {
    if (Utils::flickering(&comboTimer)) {
      drawCombo();
    }
    if (comboTimer == 0) {
      Player::resetCombo();
    }
  }
  drawTop();
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
  if (combo > 99) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, 
                    player.animation.pos.y / PIXEL_SCALE - 3, combo, 3);
  } else if (combo > 9) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, 
                    player.animation.pos.y / PIXEL_SCALE, combo, 2);
  } else if (combo > 4) {
    Utils::printNum(player.animation.pos.x / PIXEL_SCALE - cameraOffset + 10, 
                    player.animation.pos.y / PIXEL_SCALE + 2, combo, 1);
  }
}

void onComboEnd() {
  comboTimer = HUD_COUNTER_FRAMES;
}

void onDamaged() {
  damage.pos.x = player.animation.pos.x / PIXEL_SCALE;
  damage.pos.y = player.animation.pos.y / PIXEL_SCALE;
  damage.t = DAMAGE_COUNTER_FRAMES;
}

void onEmpty() {
  if (empty.t == 0) {
    empty.t = HUD_COUNTER_FRAMES;
    empty.pos.x = player.animation.pos.x / PIXEL_SCALE + 10;
    empty.pos.y = player.animation.pos.y / PIXEL_SCALE - 8;
  }
}

void onShiftMap() {
  if (damage.t > 0) {
    Level::shiftPos(&damage.pos);
  }

  if (empty.t > 0) {
    Level::shiftPos(&empty.pos);
  }
}
}
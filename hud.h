#ifndef HUD_H
#define HUD_H
#include "globals.h"
#include "player.h"
#include "bitmaps.h"

#define DAMAGE_COUNTER_FRAMES 50
#define HUD_COUNTER_FRAMES   60
#define HUD_COUNTER_IFRAMES  30

// uint8_t comboTimer;

typedef struct {
  const unsigned char *sprite;
  uint8_t t;
  int8_t f;
  position_t pos;
} hud_t;

namespace HUD {
  void init();
  void update();
  void draw();

  void update(hud_t *hud);
  void draw(hud_t hud, uint8_t frame);
  void drawTop();
  void drawCombo();

  void onDamaged();
  void onShoot();
  void onRecharge();
  void onComboEnd();
  

  void onShiftMap();

}


#endif
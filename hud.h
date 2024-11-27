#ifndef HUD_H
#define HUD_H
#include "globals.h"
#include "player.h"
#include "bitmaps.h"

#define DAMAGE_COUNTER_FRAMES 60
#define DAMAGE_COUNTER_HOLD  50
#define HUD_COUNTER_FRAMES   60
#define HUD_COUNTER_IFRAMES  30

typedef struct {
  int8_t t;
  position_t pos;
} hud_t;

namespace HUD {
  void init();
  void update();
  void draw();

  void drawHud(hud_t hud, const unsigned char *sprite);
  void drawTop();
  void drawCombo();

  void onDamaged();
  void onEmpty();
  void onComboEnd();
  

  void onShiftMap();

}


#endif
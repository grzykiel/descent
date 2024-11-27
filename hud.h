#ifndef HUD_H
#define HUD_H
#include "globals.h"
#include "player.h"
#include "bitmaps.h"

#define DAMAGE_COUNTER_FRAMES 50
#define HUD_COUNTER_FRAMES   60
#define HUD_COUNTER_IFRAMES  30

typedef struct {
  const unsigned char *sprite;  //TODO delete
  uint8_t t;
  int8_t f;                     // TODO delete
  position_t pos;
} hud_t;

namespace HUD {
  void init();
  void update();
  void draw();

  void updateHud(hud_t *hud);
  void drawHud(hud_t hud, uint8_t frame);
  void drawTop();
  void drawCombo();

  void onDamaged();
  void onShoot(); // TODO remove
  void onEmpty();
  void onRecharge();
  void onComboEnd();
  

  void onShiftMap();

}


#endif
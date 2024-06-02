#ifndef HUD_H
#define HUD_H
#include "globals.h"
#include "player.h"
#include "bitmaps.h"

typedef struct {
  const unsigned char *sprite;
  uint8_t t;
  uint8_t displayDuration;
  int8_t f;
  uint8_t flickerDuration;
  position_t pos;
} hud_t;

extern hud_t damageCounter;

namespace HUD {

  void update();
  void draw();

  void update(hud_t hud);
  void draw(hud_t hud, uint8_t frame);

  void onDamaged();


}


#endif
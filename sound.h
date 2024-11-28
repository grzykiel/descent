#include "globals.h"

#define TONE  0
#define NOISE 1
#define SWEEP 2

#define STOMP_TONE_INIT     130
#define STOMP_TONE_DURATION 12

namespace Sound {
  void init();
  void update();
  void playTone(uint16_t tone, uint8_t duration);
  void playNoise(uint16_t low, uint16_t high, uint8_t duration);
  void playSweep(uint16_t start, uint16_t end, uint8_t duration);
  void stop();
  void onIncreaseCombo();
  void onResetCombo();
}
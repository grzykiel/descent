#include "sound.h"

uint8_t framesLeft = 0;
uint8_t duration;
uint8_t soundType;
uint16_t tone1;
uint16_t tone2;
uint16_t stompTone;

namespace Sound {
  void init() {
    stompTone = STOMP_TONE_INIT;
    stop();
  }

  void update() {
    if (framesLeft == 0) return;
    
    framesLeft--;
    if (framesLeft == 0) {
      stop();
      return;
    }
    
    switch (soundType) {
      case (NOISE):
        beep1.tone(beep1.freq(random(tone1, tone2)));
        beep2.tone(beep2.freq(random(tone1, tone2)));
        break;
      case (SWEEP):
        uint16_t tone = (tone2 - tone1)*(duration - framesLeft);
        tone = tone1 + tone/duration;
        beep1.tone(beep1.freq(tone));
        beep2.tone(beep2.freq(tone));
        break;
    }
  }

  void playTone(uint16_t tone, uint8_t frames) {
    soundType = TONE;
    beep1.tone(beep1.freq(tone));
    beep2.tone(beep2.freq(tone));
    framesLeft = frames;
  }

  void playNoise(uint16_t low, uint16_t high, uint8_t frames) {
    soundType = NOISE;
    tone1 = low;
    tone2 = high;
    framesLeft = frames;
  }

  void playSweep(uint16_t start, uint16_t end, uint8_t frames) {
    soundType = SWEEP;
    tone1 = start;
    tone2 = end;
    duration = frames;
    framesLeft = frames;
  }
  
  void stop() {
    framesLeft = 0;
    beep1.noTone();
    beep2.noTone();
  }

  void onIncreaseCombo() {
    playTone(stompTone, STOMP_TONE_DURATION);
    stompTone = (stompTone*25)/24;
  }

  void onResetCombo() {
    stompTone = STOMP_TONE_INIT;
  }
}
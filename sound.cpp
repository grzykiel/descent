#include "sound.h"

uint8_t framesLeft = 0;
uint8_t duration;
uint8_t soundType;
uint16_t tone1;
uint16_t tone2;
uint16_t stompTone;
const uint16_t intro[] PROGMEM = {NOTE_E3, 400, NOTE_CS3, 800, NOTE_C3, 400, NOTE_A2, 800, TONES_END};
const uint16_t gameover[] PROGMEM = {NOTE_FS2, 400, NOTE_C2, 800, TONES_END};


namespace Sound {

  void init() {
    stompTone = STOMP_TONE_INIT;
    stop();
  }

  void playIntro() {
    stop();
    sound.tones(intro);
  }
  
  void playGameover() {
    stop();
    sound.tones(gameover);
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
        sound.tone(random(tone1, tone2));
        break;
      case (SWEEP):
        uint16_t tone = (tone2 - tone1)*(duration - framesLeft);
        tone = tone1 + tone/duration;
        sound.tone(tone);
        break;
    }
  }

  void playTone(uint16_t tone, uint8_t frames) {
    if (sound.playing()) return;
    soundType = TONE;
    sound.tone(tone, (frames*1024)/FPS);
  }

  void playNoise(uint16_t low, uint16_t high, uint8_t frames) {
    if (sound.playing()) return;
    soundType = NOISE;
    tone1 = low;
    tone2 = high;
    framesLeft = frames;
  }

  void playSweep(uint16_t start, uint16_t end, uint8_t frames) {
    if (sound.playing()) return;
    soundType = SWEEP;
    tone1 = start;
    tone2 = end;
    duration = frames;
    framesLeft = frames;
  }
  
  void stop() {
    framesLeft = 0;
    sound.noTone();
  }

  void onIncreaseCombo() {
    playTone(stompTone, STOMP_TONE_DURATION);
    stompTone = (stompTone*25)/24;
  }

  void onResetCombo() {
    stompTone = STOMP_TONE_INIT;
  }
}
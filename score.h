#ifndef SCORE_H
#define SCORE_H
#include "globals.h"

#define SCORE_MULTIPLIER 10

namespace Score {
  uint16_t getScore();
  uint16_t getHighscore();

  void init();
  void increaseScore(uint8_t s);
  void updateHighscore();
}

#endif
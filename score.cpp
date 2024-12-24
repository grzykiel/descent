#include "Arduboy2.h"
#include "score.h"

uint16_t score = 0;
uint16_t highScore = 0;
int8_t address = EEPROM_STORAGE_SPACE_START + sizeof(uint16_t);

namespace Score {

uint16_t getScore() {
  return score;
}

uint16_t getHighscore() {
  EEPROM.get(address, highScore);
  return highScore;
}

void updateHighscore() {
  if (score > highScore) {
    highScore = score;
    EEPROM.put(address, highScore);
  }
}

void init() {
  score = 0;
  // find stored data
  for (int i = EEPROM_STORAGE_SPACE_START; i < EEPROM.length() - 2 * sizeof(uint8_t); i++) {
    uint16_t data;
    EEPROM.get(i, data);
    if (data == 0xDE5C) {
      address = i + sizeof(uint16_t);
      return;
    }
  }

  // // find empty slot
  for (int i = EEPROM_STORAGE_SPACE_START; i < EEPROM.length() - 2 * sizeof(uint16_t); i += 2 * sizeof(uint16_t)) {
    uint16_t data;
    EEPROM.get(i, data);
    if (!data) {
      EEPROM.put(i, 0xDE5C);
      address = i + sizeof(uint16_t);
      EEPROM.put(address, 0);
      return;
    }
  }

  // Memory full, overwrite start
  EEPROM.put(EEPROM_STORAGE_SPACE_START, 0xDE5C);
  EEPROM.put(address, 0);
}

void increaseScore(uint8_t s) {
  score += s * SCORE_MULTIPLIER;
}

}
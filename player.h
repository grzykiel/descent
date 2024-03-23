#include "enums.h"

typedef struct {
  int8_t y = 28;
  uint8_t x = 64;
  int8_t vy = 0;
  Direction dir = Direction::left;
  uint8_t sprite = 0;
} player_t;

player_t player;
player_t playerNext;
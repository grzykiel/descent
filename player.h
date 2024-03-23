#include "enums.h"

typedef struct {
  uint8_t y = 28;
  uint8_t x = 64;
  uint8_t vy = 0;
  Direction dir = Direction::left;
} player_t;

player_t player;
player_t playerNext;
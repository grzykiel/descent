#include "enums.h"

typedef struct {
  int8_t y = 28;
  uint8_t x = 64;
  int8_t vy = 0;
  Direction dir = Direction::right;
  const unsigned char *sprite = Player::runRightSprite;
  uint8_t frame = 0;
} player_t;

player_t player;

player_t playerNext;
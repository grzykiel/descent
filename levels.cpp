#include "levels.h"

uint8_t nextRoom[ROOMSIZE];

uint8_t levelMap[MAPSIZE];

constexpr uint8_t startRoom[SCREENWIDTH] = {
  // 0x00, 0x00, 0x00, 0x00,
  // 0x00, 0x11, 0x11, 0x00,
  // 0x00, 0x10, 0x01, 0x00,
  // 0x00, 0x00, 0x00, 0x00,

  0xE8, 0x11, 0x11, 0x2E,
  0x90, 0x00, 0x00, 0x03
};

uint8_t passage;


namespace Level {

void init() {
  for (uint8_t i = 0; i < MAPSIZE; i++) {
    levelMap[i] = 0x00;
  }

  for (uint8_t i = 0; i < 8; i++) {
    levelMap[44 * 4 + i] = startRoom[i];
  }

  passage = 0x38;
}

void draw() {

  //wall boundaries
  arduboy.drawFastHLine(0, 0, 128);
  arduboy.drawFastHLine(0, 63, 128);

  // levelMap
  int xMin = ceil(player.animation.pos.x / PIXEL_SCALE / (1.0f * BLOCKSIZE)) + 8;
  int xMax = floor(player.animation.pos.x / PIXEL_SCALE / (1.0f * BLOCKSIZE)) - 8;
  xMin = max(MAPHEIGHT - 1 - xMin, 0);
  xMax = min(MAPHEIGHT - xMax, MAPHEIGHT - 1);

  for (int i = xMin; i < xMax; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      if (getMap(i, j)) {
        if (getMap(i, j) == DASH || getMap(i, j) == BLOCK) {
          Sprites::drawSelfMasked((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j * BLOCKSIZE, Tiles::wall, getMap(i, j));
        } else {
          Sprites::drawOverwrite((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j * BLOCKSIZE, Tiles::wall, getMap(i, j));
        }
      }
    }
  }
}

void update() {
  if (player.animation.pos.x / PIXEL_SCALE <= REMAP_THRESHOLD) {
    shiftMap();
  }
}

void shiftPos(position_t *pos) {
  pos->x += 128 * PIXEL_SCALE;
}

void shiftMap() {
  shiftPos(&player.animation.pos);  // TODO Player::onShiftMap();

  Bullet::onShiftMap();
  Enemies::onShiftMap();
  Particles::onShiftMap();
  HUD::onShiftMap();
  Powerups::onShiftMap();

  copyRoom(levelMap, 16 * 4, levelMap, 0);
  copyRoom(levelMap, 32 * 4, levelMap, 16 * 4);
  eraseRoom();

  uint8_t w = random(passage >> 4, passage & 0x0F);
  uint8_t c = random(0, MAPWIDTH - w + 1);

  generateWall(true, c);
  generateWall(false, MAPWIDTH - w - c);

  autoTile();
  uint8_t d = random(0, 6);
  for (int i = 0; i < d; i++) {
    generateDashes();
  }
  generateBlocks();
  generateEnemies();
  copyRoom(nextRoom, 0, levelMap, 32 * 4);
}


//TODO out of bounds checking
void copyRoom(uint8_t from[], uint8_t f, uint8_t to[], uint8_t t) {
  for (uint8_t i = 0; i < ROOMSIZE; i++) {
    to[i + t] = from[i + f];
  }
}

void autoTile() {
  for (uint8_t i = 1; i < SCREENHEIGHT - 1; i++) {
    for (uint8_t j = 0; j < SCREENWIDTH; j++) {
      if (getRoom(nextRoom, i, j) == 0) continue;
      uint8_t tile = 0;
      tile = (getRoom(nextRoom, i - 1, j) != 0) & 0x01;
      if (j == SCREENWIDTH - 1) {
        tile |= 0x02;
      } else {
        tile |= (((getRoom(nextRoom, i, j + 1) != 0) << 1) & 0x02);
      }
      tile |= (((getRoom(nextRoom, i + 1, j) != 0) << 2) & 0x04);
      if (j == 0) {
        tile |= 0x08;
      } else {
        tile |= (((getRoom(nextRoom, i, j - 1) != 0) << 3) & 0x08);
      }
      writeRoom(nextRoom, i, j, tile);
    }
  }
}

void generateWall(bool left, uint8_t edge) {
  uint8_t t = random(1, 5);
  uint8_t b = random(9, 16);
  uint8_t m = random(t, b);
  int8_t w = edge;

  for (uint8_t i = m; i > t; i--) {
    for (uint8_t j = 0; j < w; j++) {
      if (left) {
        writeRoom(nextRoom, i, j, 1);
      } else {
        writeRoom(nextRoom, i, MAPWIDTH - 1 - j, 1);
      }
    }
    w = random(0, w + 1);
  }

  w = random(0, edge);
  for (uint8_t i = m + 1; i < b; i++) {
    for (uint8_t j = 0; j < w; j++) {
      if (left) {
        writeRoom(nextRoom, i, j, 1);
      } else {
        writeRoom(nextRoom, i, MAPWIDTH - 1 - j, 1);
      }
    }
  }
}

void generateDashes() {
  uint8_t x = random(1, SCREENHEIGHT - 1);
  uint8_t y1 = random(0, SCREENWIDTH - 2);
  uint8_t y2 = random(0, 3) ? y1 + 2 : y1 + 1;
  uint8_t attempts = 0;

  while (!clearPath(x, y1, y2) && (attempts < 16 * 8)) {  //TODO #define MAX_ATTEMPTS
    x = random(1, SCREENHEIGHT - 1);
    y1 = random(0, SCREENHEIGHT - 2);
    y2 = random(0, 3) ? y1 + 2 : y1 + 1;
    attempts++;
  }

  for (uint8_t i = y1; i < y2; i++) {
    if (!getRoom(nextRoom, x, i)) writeRoom(nextRoom, x, i, DASH);
  }
}

bool clearPath(uint8_t x, uint8_t y1, uint8_t y2) {
  bool lc = true;
  bool rc = true;
  bool mc = true;

  if (y1 > 2) {
    for (uint8_t i = x - 2; i < x + 2; i++) {
      for (uint8_t j = y1 - 2; j < y1; j++) {
        if (getRoom(nextRoom, i, j)) {
          lc = false;
        }
      }
    }
  } else {
    lc = false;
  }

  if (y2 < SCREENWIDTH - 2) {
    for (uint8_t i = x - 2; i < x + 2; i++) {
      for (uint8_t j = y2; j < y2 + 2; j++) {
        if (getRoom(nextRoom, i, j)) {
          rc = false;
        }
      }
    }
  } else {
    rc = false;
  }

  for (uint8_t i = x - 1; i < x; i++) {
    for (uint8_t j = y1; j < y2; j++) {
      if (getRoom(nextRoom, i, j)) {
        mc = false;
      }
    }
  }

  return (lc || rc || mc);
}



void generateBlocks() {
  uint8_t rs = random(TOP_MARGIN, SCREENHEIGHT / 2);
  while (rs + 2 < SCREENHEIGHT - BOTTOM_MARGIN) {
    uint8_t re = random(rs + 1, SCREENHEIGHT - BOTTOM_MARGIN);
    re = min(re, SCREENHEIGHT - BOTTOM_MARGIN);
    uint8_t cs = random(0, SCREENWIDTH);
    uint8_t ce = random(cs + 1, SCREENWIDTH);

    for (int i = rs; i < re; i++) {
      for (int j = cs; j < ce; j++) {
        if (!getRoom(nextRoom, i, j) && !getRoom(nextRoom, i - 1, j) && random(0, 4) > 1) writeRoom(nextRoom, i, j, BLOCK);
      }
    }

    if (re + 1 >= SCREENHEIGHT - BOTTOM_MARGIN) break;
    rs = random(re + 1, SCREENHEIGHT - BOTTOM_MARGIN);
  }
}

void eraseRoom() {
  for (int i = 0; i < ROOMSIZE; i++) {
    nextRoom[i] = 0x00;
  }
}

void generateEnemies() {
  uint8_t i = random(1, SCREENHEIGHT - 1);
  uint8_t j = random(0, SCREENWIDTH);


  if (random(0, 2) > 0) {
    // BLOB
    while (getRoom(nextRoom, i, j)) {
      i = random(0, SCREENHEIGHT);
      j = random(0, SCREENWIDTH);
    }
    Enemies::spawn(EnemyType::blob, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  } else {
    // BAT
    while (getRoom(nextRoom, i, j) || !getRoom(nextRoom, i - 1, j) || getRoom(nextRoom, i - 1, j) == DASH) {
      i = random(1, SCREENHEIGHT - 1);
      j = random(0, SCREENWIDTH);
    }
    Enemies::spawn(EnemyType::hangingBat, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  }

  //WORM / TORTOISE
  while (getRoom(nextRoom, i, j) || !getRoom(nextRoom, i + 1, j)) {
    i = random(0, SCREENHEIGHT);
    j = random(0, SCREENWIDTH);
  }
  if (random(0, 3) < 2) {
    if (random(0, 2)) {
      Enemies::spawn(EnemyType::worm, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
    } else {
      Enemies::spawn(EnemyType::tortoise, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
    }
  } else {
    while (getRoom(nextRoom, i, j) || !getRoom(nextRoom, i + 1, j)) {
      i = random(0, SCREENHEIGHT);
      i = random(0, SCREENWIDTH);
    }
    Enemies::spawn(EnemyType::crawler, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  }
}

void destroyBlock(int16_t i, uint8_t j) {
  writeMap(i, j, 0);
  Particles::spawnBlockFragment(i, j);
  Powerups::spawnUpgrade((MAPHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
}

uint8_t getMap(int16_t i, uint8_t j) {
  if (j % 2 != 0) {
    return levelMap[i * 4 + j / 2] & 0x0F;
  }
  return (levelMap[i * 4 + j / 2] >> 4);
}

uint8_t getRoom(uint8_t room[], int16_t i, uint8_t j) {
  if (j % 2 != 0) {
    return room[i * 4 + j / 2] & 0x0F;
  }
  return (room[i * 4 + j / 2] >> 4);
}

void writeMap(int16_t i, uint8_t j, uint8_t tile) {
  if ((j % 2) != 0) {
    levelMap[i * 4 + j / 2] = (levelMap[i * 4 + j / 2] & 0xF0) | tile;
  } else {
    levelMap[i * 4 + j / 2] = (levelMap[i * 4 + j / 2] & 0x0F) | ((tile << 4) & 0xF0);
  }
}

void writeRoom(uint8_t room[], int16_t i, uint8_t j, uint8_t tile) {
  if ((j % 2) != 0) {
    room[i * 4 + j / 2] = (room[i * 4 + j / 2] & 0xF0) | tile;
  } else {
    room[i * 4 + j / 2] = (room[i * 4 + j / 2] & 0x0F) | ((tile << 4) & 0xF0);
  }
}


}
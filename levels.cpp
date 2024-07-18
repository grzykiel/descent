#include "levels.h"

uint8_t nextRoom[SCREENHEIGHT][SCREENWIDTH];
/* = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 1, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 1 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 0, 0, 0, 1, 1, 1 }
};*/

uint8_t levelMap[MAPHEIGHT][MAPWIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  // { 0, 0, 1, 1, 1, 0, 1, 1 },

  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 18, 18, 0, 0, 0 },
  { 0, 0, 18, 0, 0, 18, 0, 0 },
  { 0, 0, 18, 0, 0, 18, 0, 0 },
  { 0, 0, 0, 17, 18, 17, 0, 0 },
  { 0, 0, 0, 0, 17, 17, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 15, 9, 18, 18, 18, 18, 3, 15 },
  { 10, 0, 18, 0, 0, 0, 0, 4 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },


};

namespace Level {

void init() {
  Enemies::spawn(EnemyType::crawler, 7 * BLOCKSIZE, 4 * BLOCKSIZE);
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

  // for (int i = 0; i < MAPHEIGHT; i++) {
  //   for (int j = 0; j < MAPWIDTH; j++) {
  for (int i = xMin; i < xMax; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      if (levelMap[i][j]) {
        if (levelMap[i][j] == DASH | levelMap[i][j] == BLOCK) {
          Sprites::drawSelfMasked((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j * BLOCKSIZE, Tiles::wall, levelMap[i][j]);
        } else {
          Sprites::drawOverwrite((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j * BLOCKSIZE, Tiles::wall, levelMap[i][j]);
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


  copyMap(levelMap, 16, levelMap, 0);
  copyMap(levelMap, 32, levelMap, 16);
  eraseRoom(nextRoom);
  generateWalls(nextRoom, true);
  generateWalls(nextRoom, false);
  autoTile(nextRoom);
  generateDashes(nextRoom);
  generateBlocks(nextRoom);
  // generateEnemies(nextRoom);
  copyMap(nextRoom, 0, levelMap, 32);
}


//TODO out of bounds checking
void copyMap(uint8_t fromMap[][MAPWIDTH], uint8_t fromIndex, uint8_t toMap[][MAPWIDTH], uint8_t toIndex) {
  for (int i = 0; i < SCREENHEIGHT; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      toMap[i + toIndex][j] = fromMap[i + fromIndex][j];
    }
  }
}

void autoTile(uint8_t room[][SCREENWIDTH]) {
  for (int i = 0; i < SCREENHEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      if (room[i][j]) {
        int a = (i == 0) ? 1 : (room[i - 1][j] > 0) * 1;
        int b = (j == SCREENWIDTH - 1) ? 2 : (room[i][j + 1] > 0) * 2;
        int c = (i == SCREENHEIGHT - 1) ? 4 : (room[i + 1][j] > 0) * 4;
        int d = (j == 0) ? 8 : (room[i][j - 1] > 0) * 8;
        room[i][j] = a + b + c + d + 1;
      }
    }
  }
}

void generateWalls(uint8_t room[][SCREENWIDTH], bool left) {
  int p = random(TOP_MARGIN, SCREENHEIGHT / 2);
  int r = random(p, SCREENHEIGHT - BOTTOM_MARGIN);
  int q = random(p, r);
  int w = 0;

  for (int i = p; i < q; i++) {
    w = random(w, WALL_WIDTH_MAX);
    for (int j = 0; j < w; j++) {
      if (left) {
        room[i][j] = 1;
      } else {
        room[i][SCREENWIDTH - 1 - j] = 1;
      }
    }
  }

  for (int i = q; i < r; i++) {
    w = random(1, w + 1);
    for (int j = 0; j < w; j++) {
      if (left) {
        room[i][j] = 1;
      } else {
        room[i][SCREENWIDTH - 1 - j] = 1;
      }
    }
  }
}

void generateDashes(uint8_t room[][SCREENWIDTH]) {
  uint8_t i = random(1, SCREENHEIGHT / 2);
  while (i < SCREENHEIGHT - BOTTOM_MARGIN) {
    uint8_t cs = 0;
    while (room[i][cs] && cs < SCREENWIDTH) {
      cs++;
    }

    uint8_t ce = cs + 1;
    while (!room[i][ce] && ce < SCREENWIDTH) {
      ce++;
    }

    placeDashes(room, i, cs, ce);

    if (i + 2 >= SCREENHEIGHT - BOTTOM_MARGIN) break;
    i = random(i + 2, SCREENHEIGHT - BOTTOM_MARGIN);
  }
}

void placeDashes(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce) {
  uint8_t gap = ce - cs;
  uint8_t w = 0;
  uint8_t c;

  if (gap >= 5) {
    w = random(DASH_WIDTH_MIN, DASH_WIDTH_MAX);
    if (w == 3) {
      c = (random(0, 2) == 1) ? 0 : ce - w;
    } else if (w == 2) {
      c = random(cs, ce - w);
    }
  } else if (gap == 4) {
    w = DASH_WIDTH_MIN;
  } else {
    return;
  }

  for (int i = c; i < (c + w); i++) {
    if (!room[row - 1][i] && !room[row + 1][i]
        && !room[row - 1][max(0, i - 1)] && !room[row - 1][min(MAPWIDTH, i + 1)]
        && !room[row + 1][max(0, i - 1)] && !room[row + 1][min(MAPWIDTH, i + 1)]) {
      room[row][i] = DASH;
    }
  }
}

void generateBlocks(uint8_t room[][SCREENWIDTH]) {
  uint8_t rs = random(TOP_MARGIN, SCREENHEIGHT / 2);
  while (rs + 2 < SCREENHEIGHT - BOTTOM_MARGIN) {
    uint8_t re = random(rs + 1, SCREENHEIGHT - BOTTOM_MARGIN);
    re = min(re, SCREENHEIGHT - BOTTOM_MARGIN);
    uint8_t cs = random(0, SCREENWIDTH);
    uint8_t ce = random(cs + 1, SCREENWIDTH);

    for (int i = rs; i < re; i++) {
      for (int j = cs; j < ce; j++) {
        if (!room[i][j] && !room[i - 1][j] && random(0, 4) > 1) room[i][j] = BLOCK;
      }
    }

    if (re + 1 >= SCREENHEIGHT - BOTTOM_MARGIN) break;
    rs = random(re + 1, SCREENHEIGHT - BOTTOM_MARGIN);
  }
}


void eraseRoom(uint8_t room[][SCREENWIDTH]) {
  for (int i = 0; i < SCREENHEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      room[i][j] = 0;
    }
  }
}

void generateEnemies(uint8_t room[][SCREENWIDTH]) {
  uint8_t i = random(1, SCREENHEIGHT - 1);
  uint8_t j = random(0, SCREENWIDTH);

  if (random(0, 2) > 0) {
    // BLOB
    while (room[i][j]) {
      i = random(0, SCREENHEIGHT);
      j = random(0, SCREENWIDTH);
    }
    Enemies::spawn(EnemyType::blob, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  } else {
    // BAT
    while (room[i][j] || !room[i - 1][j] || room[i - 1][j] == DASH) {
      i = random(1, SCREENHEIGHT - 1);
      j = random(0, SCREENWIDTH);
    }
    Enemies::spawn(EnemyType::hangingBat, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  }

  //WORM / TORTOISE
  while (room[i][j] || !room[i + 1][j]) {
    i = random(0, SCREENHEIGHT);
    j = random(0, SCREENWIDTH);
  };
  if (random(0, 2) > 0) {
    Enemies::spawn(EnemyType::worm, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  } else {
    Enemies::spawn(EnemyType::tortoise, (SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE);
  }
}

void destroyBlock(int16_t i, uint8_t j) {
  levelMap[i][j] = 0;
  Particles::spawnBlockFragment(i, j);
}


}
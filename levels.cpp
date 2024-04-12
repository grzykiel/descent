#include "levels.h"

#include "game.h"
#include "player.h"
#include "bitmaps.h"
// #include "globals.h"

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
  { 1, 2, 3, 0, 0, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 15, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },

  { 1, 1, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 1, 1 },

  { 1, 1, 1, 0, 0, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 1, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 1, 1, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 0, 0, 0, 1, 1, 1 },
  { 1, 1, 0, 0, 0, 1, 1, 1 }
};

namespace Level {

void init() {
}

void draw() {

  // arduboy.print(player.x);
  arduboy.drawRect(-1, 0, 130, 64);

  // levelMap
  int xMin = ceil(player.x / (1.0f * BLOCKSIZE)) + 8;
  int xMax = floor(player.x / (1.0f * BLOCKSIZE)) - 8;
  xMin = max(MAPHEIGHT - 1 - xMin, 0);
  xMax = min(MAPHEIGHT - 1 - xMax, MAPHEIGHT - 1);

  for (int i = 0; i < MAPHEIGHT; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      if (levelMap[i][j]) {
        if (levelMap[i][j] == DASH) {
          Sprites::drawSelfMasked((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j*BLOCKSIZE, Tiles::wall, DASH);
        } else {
          Sprites::drawOverwrite((MAPHEIGHT - i - 1) * BLOCKSIZE - cameraOffset, j * BLOCKSIZE, Tiles::wall, levelMap[i][j]);
        }
      }
    }
  }
}

void update() {
  if (player.x <= REMAP_THRESHOLD) {
    shiftMap();
  }
}

// TODO modify to generate
void shiftMap() {
  player.x = SCREENMID + 128;  //TODO #define
  copyMap(levelMap, 16, levelMap, 0);
  copyMap(levelMap, 32, levelMap, 16);
  eraseRoom(nextRoom);
  generateWalls(nextRoom, true);
  generateWalls(nextRoom, false);
  autoTile(nextRoom);
  generateDashes(nextRoom);
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
  int p = random(1, SCREENHEIGHT / 2);
  int r = random(p, SCREENHEIGHT - 2);
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
	uint8_t i = random(1, SCREENHEIGHT/2);
	while (i < SCREENHEIGHT - 2) {
		uint8_t cs = 0;
		while (room[i][cs] && cs < SCREENWIDTH) {
			cs++;
		}
		
		uint8_t ce = cs+1;
		while (!room[i][ce] && ce < SCREENWIDTH) {
			ce++;
		}
		
		placeDashes(room, i, cs, ce);
		
		if (i+2 >= SCREENHEIGHT - 2) break;
		i = random(i+2, SCREENHEIGHT - 2);
	}
}

void placeDashes(uint8_t room[][SCREENWIDTH], uint8_t row, uint8_t cs, uint8_t ce) {
	uint8_t gap = ce - cs;
	uint8_t w = 0;
	uint8_t c;
	
	if (gap >= 5) {
		w = random(2, 4);
		if (w == 3) {
			c = (random(0, 2) == 1) ? 0 : ce - w;
		} else if (w == 2) {
			c = random(cs, ce - w);
		}
	} else if (gap == 4) {
		w = 2;
	} else {
		return;
	}
	
	for (int i=c; i<(c+w); i++) {
		if (!(room[row-1][i]) && !(room[row+1][i])) {
			room[row][i] = DASH;
		}
	}
}


void eraseRoom(uint8_t room[][SCREENWIDTH]) {
  for (int i = 0; i < SCREENHEIGHT; i++) {
    for (int j = 0; j < SCREENWIDTH; j++) {
      room[i][j] = 0;
    }
  }
}

}
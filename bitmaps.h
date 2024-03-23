#define N_WALKFRAMES 4

namespace Player {
  const unsigned char PROGMEM runLeftSprite[] = {
  8, 8,
  // Frame 0
  0x36, 0x24, 0x7D, 0x3C, 0x3C, 0x28, 0x28, 0x1C,

  // Frame 1
  0x43, 0x7E, 0x3C, 0xBC, 0x29, 0x28, 0x1C, 0x00,

  // Frame 2
  0x36, 0x24, 0x7C, 0x3D, 0x3C, 0x28, 0x28, 0x1C,

  // Frame 3
  0x1C, 0x38, 0x3E, 0x3C, 0x3C, 0x28, 0x28, 0x1C,

  // Frame 4
  0x1C, 0x18, 0x3C, 0x3C, 0x3C, 0x28, 0x28, 0x1C,
};

const unsigned char PROGMEM runRightSprite[] = {
  8, 8,

  // Frame 0
  0x6C, 0x24, 0xBE, 0x3C, 0x3C, 0x14, 0x14, 0x38,

  // Frame 1
  0xC2, 0x7E, 0x3C, 0x3D, 0x94, 0x14, 0x38, 0x00,

  // Frame 2
  0x6C, 0x24, 0x3E, 0xBC, 0x3C, 0x14, 0x14, 0x38,

  // Frame 3
  0x38, 0x1C, 0x7C, 0x3C, 0x3C, 0x14, 0x14, 0x38,

  // Frame 4
  0x38, 0x18, 0x3C, 0x3C, 0x3C, 0x14, 0x14, 0x38,

};
}
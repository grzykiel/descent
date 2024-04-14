#ifndef BITMAPS_H
#define BITMAPS_H

#define N_WALKFRAMES 4

namespace Player {
const unsigned char PROGMEM runLeftSprite[] = {
  8,   8,
  // Frame 0
  0x36,  0x24,  0x7D,  0x3C,  0x3C,  0x28,  0x28,  0x1C,

  // Frame 1
  0x43,  0x7E,  0x3C,  0xBC,  0x29,  0x28,  0x1C,  0x00,

  // Frame 2
  0x36,  0x24,  0x7C,  0x3D,  0x3C,  0x28, 0x28,  0x1C,

  // Frame 3
  0x1C,  0x38,  0x3E,  0x3C,  0x3C,  0x28,  0x28,  0x1C,

  // Frame 4
  0x1C,  0x18,  0x3C,  0x3C,  0x3C,  0x28,  0x28,  0x1C,
};

const unsigned char PROGMEM runRightSprite[] = {
  8,  8,

  // Frame 0
  0x6C,  0x24,  0xBE,  0x3C,  0x3C,  0x14,  0x14,  0x38,

  // Frame 1
  0xC2,  0x7E,  0x3C,  0x3D,  0x94,  0x14,  0x38,  0x00,

  // Frame 2
  0x6C,  0x24,  0x3E,  0xBC,  0x3C,  0x14,  0x14,  0x38,

  // Frame 3
  0x38,  0x1C,  0x7C,  0x3C,  0x3C,  0x14,  0x14,  0x38,

  // Frame 4
  0x38,  0x18,  0x3C,  0x3C,  0x3C,  0x14,  0x14,  0x38,

};
}

namespace Tiles {

const unsigned char PROGMEM block[] = {
  8, 8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF
};


const unsigned char PROGMEM wall[] = {
  8,   8,

  	// Frame 0
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 1
		0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E,
			
		// Frame 2
		0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
			
		// Frame 3
		0xFE, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFE,
			
		// Frame 4
		0xFE, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			
		// Frame 5
		0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E,
			
		// Frame 6
		0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
			
		// Frame 7
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFE,
			
		// Frame 8
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			
		// Frame 9
		0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
			
		// Frame 10
		0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
			
		// Frame 11
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
			
		// Frame 12
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 13
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
			
		// Frame 14
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
			
		// Frame 15
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
			
		// Frame 16
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 17 Dash
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x7E,
			
		// Frame 18 Block
		0x00, 0x4E, 0x6F, 0x67, 0x00, 0x79, 0x73, 0x3B,
};
}

namespace ShootShoes {
  const unsigned char PROGMEM muzzleFlash[] = {
    8, 8,
		0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C,
  };

  const unsigned char PROGMEM bullet[] = {
    8, 8,
    // Frame 0
			0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x24,
			
			// Frame 1
			0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x24, 0x00,
			
			// Frame 3
			0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x24, 0x00, 0x00,
			
			// Frame 4
			0x18, 0x3C, 0x3C, 0x24, 0x00, 0x00, 0x00, 0x00,
			
			// Frame 5
			0x18, 0x3C, 0x3C, 0x3C, 0x24, 0x00, 0x00, 0x00,
			
			// Frame 6
			0x18, 0x3C, 0x3C, 0x24, 0x00, 0x00, 0x00, 0x00,
			
			// Frame 7
			0x18, 0x3C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,
			
			// Frame 8
			0x18, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };
}




#endif
#ifndef BITMAPS_H
#define BITMAPS_H

namespace Player {
constexpr unsigned char PROGMEM runLeftSprite[] = {
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

constexpr unsigned char PROGMEM runRightSprite[] = {
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

constexpr unsigned char PROGMEM jumpLeftSprite[] {
  8, 8,
  // Frame 0
	0x36, 0x24, 0x3C, 0x3C, 0xBD, 0x28, 0x28, 0x1C,
			
	// Frame 1
	0x30, 0x26, 0x3C, 0xBD, 0x3C, 0x3C, 0x28, 0x08,
			
	// Frame 2
	0x00, 0x36, 0x3C, 0x3C, 0xBD, 0x28, 0x28, 0x1C,
			
	// Frame 3
	0x00, 0x12, 0x3E, 0x3C, 0x3C, 0xA9, 0x28, 0x1C,
			
	// Frame 4
	0x00, 0x12, 0x3E, 0x3C, 0x3C, 0x28, 0xA9, 0x1C,
};

constexpr unsigned char PROGMEM jumpRightSprite[] = {
  8, 8,
  // Frame 0
	0x6C, 0x24, 0x3C, 0x3C, 0xBD, 0x14, 0x14, 0x38,
			
	// Frame 1
	0x0C, 0x64, 0x3C, 0xBD, 0x3C, 0x3C, 0x14, 0x10,
		
	// Frame 2
	0x00, 0x6C, 0x3C, 0x3C, 0xBD, 0x14, 0x14, 0x38,
		
	// Frame 3
	0x00, 0x48, 0x7C, 0x3C, 0x3C, 0x95, 0x14, 0x38,
			
	// Frame 4
	0x00, 0x48, 0x7C, 0x3C, 0x3C, 0x14, 0x95, 0x38,
};

constexpr unsigned char PROGMEM bounceLeftSprite[] = {
  8, 8,
  // Frame 0
	0x00, 0x12, 0x3E, 0xBD, 0x3C, 0x28, 0x28, 0x1C,
			
	// Frame 1
	0x00, 0x12, 0x3E, 0x3C, 0xBD, 0x28, 0x28, 0x1C,
			
	// Frame 2
	0x00, 0x12, 0x3E, 0x3C, 0x3C, 0xA9, 0x28, 0x1C,

  // Frame 3
	0x00, 0x12, 0x3E, 0x3C, 0x3C, 0x28, 0xA9, 0x1C,

};

constexpr unsigned char PROGMEM bounceRightSprite[] = {
  8, 8,
  // Frame 0
  0x00, 0x48, 0x7C, 0xBD, 0x3C, 0x14, 0x14, 0x38,
			
	// Frame 1
	0x00, 0x48, 0x7C, 0x3C, 0xBD, 0x14, 0x14, 0x38,
			
	// Frame 2
	0x00, 0x48, 0x7C, 0x3C, 0x3C, 0x95, 0x14, 0x38,

  // Frame 3
  0x00, 0x48, 0x7C, 0x3C, 0x3C, 0x14, 0x95, 0x38,

};

}

namespace Enemies {
  constexpr unsigned char PROGMEM blob[] = {
    8, 8,
		// Frame 0
		0x00, 0x66, 0x99, 0x81, 0x42, 0x3C, 0x00, 0x00,
			
		// Frame 1
		0x00, 0x36, 0x49, 0x41, 0x41, 0x22, 0x1C, 0x00,
  };

  constexpr unsigned char PROGMEM batHanging[] = {
    8, 8,
		0x00, 0x00, 0x00, 0x14, 0x3E, 0x3E, 0x1C, 0x08
  };

  constexpr unsigned char PROGMEM batLeft[] = {
    8, 8,
    // Left0
		0x00, 0x08, 0x1C, 0x7E, 0x95, 0x00, 0x00, 0x00,
			
		// Left1
		0x00, 0x00, 0x88, 0x5D, 0x3E, 0x14, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM batRight[] = {
    8, 8,
    // Right0
		0x00, 0x10, 0x38, 0x7E, 0xA9, 0x00, 0x00, 0x00,
			
		// Right1
		0x00, 0x00, 0x11, 0xBA, 0x7C, 0x28, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM wormLeft[] = {
    4, 4,
    // Frame 0
		0x09, 0x06, 0x00, 0x00,
			
		// Frame 1
		0x05, 0x05, 0x02, 0x00,
  };

  constexpr unsigned char PROGMEM wormRight[] = {
    4, 4,
    // Frame 0
		0x05, 0x05, 0x02, 0x00,

    // Frame 1
		0x09, 0x06, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM crawler[] = {
    8, 8,
    // up
		0x7C, 0xD6, 0x7C, 0xAA, 0x00, 0x00, 0x00, 0x00,
			
		// right
		0x0A, 0x07, 0x0D, 0x07, 0x0D, 0x07, 0x0A, 0x00,
			
		// down
		0x00, 0x00, 0x00, 0x00, 0x55, 0x3E, 0x6B, 0x3E,
			
		// left
		0x00, 0x50, 0xE0, 0xB0, 0xE0, 0xB0, 0xE0, 0x50,
  };

  constexpr unsigned char PROGMEM tortoiseLeft[] = {
    8, 8,
    // Left0
			0x84, 0x78, 0x34, 0x06, 0x00, 0x00, 0x00, 0x00,
			
			// Left1
			0x24, 0x3C, 0x1A, 0x03, 0x00, 0x00, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM tortoiseRight[] = {
    8, 8,
    // Right0
		0x21, 0x1E, 0x2C, 0x60, 0x00, 0x00, 0x00, 0x00,
			
		// Right1
		0x24, 0x3C, 0x58, 0xC0, 0x00, 0x00, 0x00, 0x00,
  };
}



namespace Tiles {

constexpr unsigned char PROGMEM wall[] = {
  8,  8,
  // Frame 0
	0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E,
		
	// Frame 1 - BLOCK
	// 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
  0x00, 0x4E, 0x6F, 0x67, 0x00, 0x79, 0x73, 0x3B,

		
	// Frame 2
	0xFE, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFE,
		
	// Frame 3
	0xFE, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		
	// Frame 4 - DASH
	// 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x7E,

	// Frame 5
	0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
		
	// Frame 6
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFE,
		
	// Frame 7
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		
	// Frame 8
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
		
	// Frame 9
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		
	// Frame 10
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
			
	// Frame 11
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		
	// Frame 12
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
		
	// Frame 13
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		
	// Frame 14
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
		
	// Frame 15 - BLANK
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
}

namespace ShootShoes {
  constexpr unsigned char PROGMEM muzzleFlash[] = {
    8, 8,
		0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C,
  };

  constexpr unsigned char PROGMEM bullet[] = {
    8, 8,
    // Frame 0
		0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x24,
		
		// Frame 1
		0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x24, 0x00,
		
		// Frame 2
		0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x24, 0x00, 0x00,

    // Frame 3
    0x18, 0x3C, 0x3C, 0x3C, 0x24, 0x00, 0x00, 0x00,
		
		// Frame 4
		0x18, 0x3C, 0x3C, 0x24, 0x00, 0x00, 0x00, 0x00,
		
		// Frame 5
    0x18, 0x3C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,

    // Frame 6
    0x18, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		
  };
}

namespace Particles {
  constexpr unsigned char PROGMEM blockFragmentsSprite[] = {
    16, 16,
		// Frame 0
		0x00, 0x00, 0x00, 0x38, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x0C, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1C, 0x0E, 0x00, 0x00,
		
		// Frame 1
		0x00, 0x00, 0x1C, 0x1E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x06, 0x00,
		0x00, 0x00, 0x20, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x38, 0x1C, 0x00,
		
		// Frame 2
		0x00, 0x0E, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03,
		0x00, 0x40, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x70, 0x38,
	};

  constexpr unsigned char PROGMEM recharge[] = {
    16, 16,
    // Frame 0
		0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		
		// Frame 1
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		
		// Frame 2
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
		
		// Frame 3
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
		
		// Frame 4
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  };

  constexpr unsigned char PROGMEM flame[]  = {
    16, 12,
    // Frame 0
		0x18, 0x0C, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x06, 0x04, 0x0C, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 1
		0x00, 0x00, 0x04, 0x02, 0x03, 0x03, 0x02, 0x06, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x04, 0x0C, 0x0C, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 2
		0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x06, 0x0C, 0x98, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 3
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0C, 0x98, 0xB0, 0xE0, 0xE0, 0x40, 0x40, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 4
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0x40, 0x40, 0x40,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
  };

  constexpr unsigned char PROGMEM explosionSprite[] = {
    8, 8,
    // Frame 0
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18,
		0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		
		// Frame 1
		0x00, 0x00, 0x3C, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E,
		0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x3C, 0x00, 0x00,
		
		// Frame 2
		0x3C, 0x3C, 0x7E, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C,
		
		// Frame 3
		0x3C, 0x3C, 0x7E, 0x7E, 0xFF, 0xFF, 0xF7, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C,
		
		// Frame 4
		0x3C, 0x3C, 0x7E, 0x7E, 0xFF, 0xFF, 0xE7, 0xFF,
		0xE7, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C,
		
		// Frame 5
		0x3C, 0x3C, 0x7E, 0x7E, 0xE7, 0xFF, 0xC3, 0xFF,
		0xC3, 0xFF, 0xE7, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C,
		
		// Frame 6
		0x3C, 0x3C, 0x66, 0x7E, 0xC3, 0xFF, 0x81, 0xFF,
		0x81, 0xFF, 0xC3, 0xFF, 0x66, 0x7E, 0x3C, 0x3C,
		
		// Frame 7
		0x00, 0x3C, 0x00, 0x7E, 0x00, 0xFF, 0x00, 0xFF,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0x7E, 0x00, 0x3C,
  };

  constexpr unsigned char PROGMEM popSprite[] = {
    16, 16,
    // Frame 0
		0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
			
		// Frame 1
		0x00, 0x80, 0x50, 0x18, 0x0C, 0x04, 0x00, 0x04, 0x06, 0x06, 0x00, 0x08, 0x18, 0xD0, 0x80, 0x00,
		0x00, 0x01, 0x0B, 0x18, 0x10, 0x60, 0x60, 0x00, 0x20, 0x60, 0x10, 0x30, 0x1C, 0x05, 0x01, 0x00,
			
		// Frame 2
    0x80, 0x50, 0x08, 0x02, 0x02, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x04, 0x0C, 0x48, 0x80,
		0x00, 0x12, 0x20, 0x20, 0x00, 0x80, 0x80, 0x40, 0x00, 0xC0, 0x00, 0x20, 0x40, 0x18, 0x08, 0x02,
  };

  constexpr unsigned char PROGMEM smokeSprite[] = {
    16, 16,
    // Frame 0
		0x00, 0x00, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xF8, 0xF8, 0xF0, 0x60, 0x00, 0x00,
		0x00, 0x00, 0x0E, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x1F, 0x3F, 0x3F, 0x1E, 0x0C, 0x00, 0x00,
		
		// Frame 1
		0x00, 0x70, 0xF8, 0x1C, 0x0E, 0x06, 0x06, 0xC4, 0x60, 0x20, 0x04, 0x0C, 0x38, 0x30, 0x00, 0x00,
		0x00, 0x0C, 0x3E, 0x79, 0x70, 0x60, 0x20, 0x00, 0x00, 0x20, 0x60, 0x72, 0x3C, 0x18, 0x00, 0x00,
		
		// Frame 2
		0x38, 0x0C, 0x06, 0x03, 0x01, 0x01, 0x00, 0x60, 0x20, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 0x00,
		0x30, 0x60, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x00, 0x00,
		
		// Frame 3
		0x10, 0x00, 0x02, 0x01, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00,
		0x00, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM clinkSprite[] = {
    4, 4,
    // Frame 0
		0x00, 0x00, 0x06, 0x06,
		0x06, 0x06, 0x00, 0x00,
		
		// Frame 1
		0x06, 0x06, 0x0F, 0x0F,
		0x0F, 0x0F, 0x06, 0x06,
		
		// Frame 2
		0x06, 0x06, 0x09, 0x0F,
		0x09, 0x0F, 0x06, 0x06,
		
		// Frame 3
		0x00, 0x06, 0x00, 0x0F,
		0x00, 0x0F, 0x00, 0x06,
  };
}

namespace HUD {
  constexpr unsigned char PROGMEM minusOne[] = {
		8, 8,	
		// -1
		0x00, 0x38, 0x10, 0x13, 0x18, 0x00, 0x00, 0x00,
	};

  constexpr unsigned char PROGMEM hp[] = {
    4, 24,
    // Frame 0
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 1
		0x00, 0x00, 0x00, 0x00,
		0x08, 0x1C, 0x3E, 0x14,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 2
		0x00, 0x80, 0xC0, 0x80,
		0x41, 0xE3, 0xF7, 0xA2,
		0x00, 0x00, 0x01, 0x00,
		
		// Frame 3
		0x20, 0x70, 0xF8, 0x50,
		0x08, 0x1C, 0xBE, 0x14,
		0x02, 0x07, 0x0F, 0x05,
		
		// Frame 4
		0x04, 0x8E, 0xDF, 0x8A,
		0x41, 0xE3, 0xF7, 0xA2,
		0x10, 0x38, 0x7D, 0x28,
		
		// Frame 5
		0x80, 0x00, 0x80, 0x80,
		0x23, 0x73, 0xF8, 0x53,
		0x00, 0x00, 0x00, 0x00,
  };

  constexpr unsigned char PROGMEM ammo[] = {
    4, 24,
    // Frame 0
		0x5C, 0x44, 0xCC, 0xDC,
		0x85, 0x9D, 0x95, 0xDD,
		0x48, 0x1C, 0x54, 0x55,
		
		// Frame 1
		0x00, 0x00, 0x00, 0x00,
		0x08, 0x00, 0x08, 0x08,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 2
		0x00, 0x00, 0x00, 0x00,
		0x14, 0x00, 0x14, 0x14,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 3
		0x00, 0x00, 0x00, 0x00,
		0x2A, 0x00, 0x2A, 0x2A,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 4
		0x00, 0x00, 0x00, 0x00,
		0x55, 0x00, 0x55, 0x55,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 5
		0x80, 0x00, 0x80, 0x80,
		0xAA, 0x00, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00,
		
		// Frame 6
		0x40, 0x00, 0x40, 0x40,
		0x55, 0x00, 0x55, 0x55,
		0x01, 0x00, 0x01, 0x01,
		
		// Frame 7
		0xA0, 0x00, 0xA0, 0xA0,
		0xAA, 0x00, 0xAA, 0xAA,
		0x02, 0x00, 0x02, 0x02,
		
		// Frame 8
		0x50, 0x00, 0x50, 0x50,
		0x55, 0x00, 0x55, 0x55,
		0x05, 0x00, 0x05, 0x05,
		
		// Frame 9
		0xA8, 0x00, 0xA8, 0xA8,
		0xAA, 0x00, 0xAA, 0xAA,
		0x0A, 0x00, 0x0A, 0x0A,
		
		// Frame 10
		0x54, 0x00, 0x54, 0x54,
		0x55, 0x00, 0x55, 0x55,
		0x15, 0x00, 0x15, 0x15,
		
		// Frame 11
		0xAA, 0x00, 0xAA, 0xAA,
		0xAA, 0x00, 0xAA, 0xAA,
		0x2A, 0x00, 0x2A, 0x2A,
		
		// Frame 12
		0x55, 0x00, 0x55, 0x55,
		0x55, 0x00, 0x55, 0x55,
		0x55, 0x00, 0x55, 0x55,
  };
}

namespace Powerups {
	constexpr unsigned char PROGMEM upgradeSprite[] = {
		8, 8,
    // 0 Heart
		0x10, 0x38, 0x7C, 0x7C, 0x28, 0x00, 0x00, 0x00,
		
		// 1 Heart Container
		0x3E, 0x77, 0x63, 0x41, 0x41, 0x6B, 0x3E, 0x00,
		
		// 2 Ammo
		0x3E, 0x41, 0x55, 0x41, 0x55, 0x55, 0x41, 0x3E,
		
		// 3 Shotgun
		0x3E, 0x61, 0x67, 0x79, 0x61, 0x7F, 0x3E, 0x00,
		
		// 4 Laser
		0x3E, 0x61, 0x79, 0x79, 0x79, 0x7F, 0x3E, 0x00,
		
		// 5 Machine Gun
		0x3E, 0x55, 0x41, 0x41, 0x49, 0x7F, 0x3E, 0x00,	
	};

}

namespace Fonts {
	constexpr unsigned char PROGMEM font_4x4[] = {
		4, 4,
		// 0
			0x07, 0x05, 0x05, 0x07,
			
			// 1
			0x07, 0x02, 0x02, 0x03,
			
			// 2
			0x07, 0x03, 0x04, 0x07,
			
			// 3
			0x07, 0x04, 0x06, 0x07,
			
			// 4
			0x04, 0x04, 0x07, 0x05,
			
			// 5
			0x07, 0x06, 0x01, 0x07,
			
			// 6
			0x07, 0x05, 0x07, 0x01,
			
			// 7
			0x04, 0x04, 0x04, 0x07,
			
			// 8
			0x07, 0x07, 0x05, 0x06,
			
			// 9
			0x04, 0x04, 0x07, 0x07,
			
			// 10 A
			0x05, 0x07, 0x05, 0x02,
			
			// 11 B
			0x07, 0x07, 0x05, 0x03,
			
			// 12 C
			0x06, 0x01, 0x01, 0x06,
			
			// 13 D
			0x03, 0x05, 0x05, 0x03,
			
			// 14 E
			0x07, 0x01, 0x03, 0x07,
			
			// 15 F
			0x01, 0x03, 0x01, 0x07,
			
			// 16 G
			0x06, 0x05, 0x01, 0x06,
			
			// 17 H
			0x05, 0x05, 0x07, 0x05,
			
			// 18 I
			0x07, 0x02, 0x02, 0x07,
			
			// 19 J
			0x02, 0x05, 0x04, 0x04,
			
			// 20 K
			0x05, 0x05, 0x03, 0x05,
			
			// 21 L
			0x07, 0x01, 0x01, 0x01,
			
			// 22 M
			0x05, 0x05, 0x07, 0x07,
			
			// 23 N
			0x05, 0x05, 0x05, 0x07,
			
			// 24 O
			0x02, 0x05, 0x05, 0x02,
			
			// 25 P
			0x01, 0x03, 0x05, 0x03,
			
			// 26 Q
			0x06, 0x05, 0x05, 0x02,
			
			// 27 R
			0x05, 0x03, 0x05, 0x03,
			
			// 28 S
			0x07, 0x06, 0x01, 0x07,
			
			// 29 T
			0x02, 0x02, 0x02, 0x07,
			
			// 30 U
			0x07, 0x05, 0x05, 0x05,
			
			// 31 V
			0x02, 0x05, 0x05, 0x05,
			
			// 32 W
			0x07, 0x07, 0x05, 0x05,
			
			// 33 X
			0x05, 0x02, 0x02, 0x05,
			
			// 34 Y
			0x02, 0x02, 0x05, 0x05,
			
			// 35 Z
			0x07, 0x03, 0x04, 0x07,
			
			// 36 COLN
			0x01, 0x00, 0x01, 0x00,
			
			// 37 EXCL
			0x01, 0x00, 0x01, 0x01,
			
			// 38 QSTN
			0x01, 0x00, 0x02, 0x01,
	};

	constexpr unsigned char PROGMEM font_5x4[] = {
		5, 4,
		// Frame 0
			0x02, 0x05, 0x05, 0x05, 0x02,
			
			// Frame 1
			0x07, 0x02, 0x02, 0x02, 0x03,
			
			// Frame 2
			0x07, 0x01, 0x02, 0x04, 0x03,
			
			// Frame 3
			0x03, 0x04, 0x02, 0x04, 0x03,
			
			// Frame 4
			0x04, 0x04, 0x07, 0x05, 0x05,
			
			// Frame 5
			0x03, 0x04, 0x02, 0x01, 0x07,
			
			// Frame 6
			0x02, 0x05, 0x03, 0x01, 0x06,
			
			// Frame 7
			0x02, 0x02, 0x04, 0x04, 0x07,
			
			// Frame 8
			0x02, 0x05, 0x02, 0x05, 0x02,
			
			// Frame 9
			0x03, 0x04, 0x06, 0x05, 0x02,

      // music note
      0x03, 0x03, 0x0A, 0x06, 0x02
	};

  constexpr unsigned char PROGMEM titleFont[] = {
    8, 8,
    // 0 D
			0x7F, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x7F,
			
			// 1 E
			0x7F, 0x8F, 0x7F, 0x0F, 0xCF, 0xCF, 0xCF, 0x7F,
			
			// 2 S
			0x7F, 0xE0, 0x7E, 0x0F, 0x0F, 0xCF, 0xFF, 0x7E,
			
			// 3 C
			0x7E, 0xCF, 0x0F, 0xCF, 0xCF, 0xCF, 0xCF, 0x7E,
			
			// 4 N
			0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xEF, 0xDF, 0xCF,
			
			// 5 T
			0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFF,
  };

  constexpr unsigned char GameOver[] PROGMEM = {
    7, 28,
    // GAME
		0xFE, 0xC3, 0xD9, 0xC9, 0xF9, 0xC3, 0x7E,
		0xFF, 0x6C, 0x6C, 0x60, 0x6C, 0x71, 0xDF,
		0xFF, 0x37, 0x37, 0x35, 0x30, 0x32, 0xFF,
		0x0F, 0x08, 0x0F, 0x04, 0x0F, 0x08, 0x0F,
			
		// OVER
		0x3E, 0x63, 0xD9, 0xD9, 0xD9, 0xE3, 0xBE,
		0xCE, 0x5B, 0x75, 0x6C, 0x6C, 0x6C, 0xFF,
		0xFF, 0x30, 0x3E, 0x28, 0x3E, 0x30, 0xFF,
		0x0F, 0x0B, 0x0C, 0x0B, 0x0B, 0x0C, 0x07,
  };
}


#endif
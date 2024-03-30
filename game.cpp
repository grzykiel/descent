#include "game.h"
#include "levels.h"
#include "player.h"
#include "bitmaps.h"

namespace Game {
void loop() {
  input();
  update();
  draw();
}

void input() {
  if (arduboy.justPressed(left_btn)) {
    player.dir = Direction::left;
    player.sprite = Player::runLeftSprite;
  } else if (arduboy.justPressed(right_btn)) {
    player.dir = Direction::right;
    player.sprite = Player::runRightSprite;
  }

  if (arduboy.pressed(left_btn)) {
    player.vy = -walkSpeed;
  } else if (arduboy.pressed(right_btn)) {
    player.vy = walkSpeed;
  } else if (arduboy.notPressed(left_btn | right_btn)) {
    player.vy = 0;
  }

  if (arduboy.pressed(up_btn)) {
    player.vx = walkSpeed;
  } else if (arduboy.pressed(down_btn)) {
    player.vx = -walkSpeed;
  } else if (arduboy.notPressed(up_btn | down_btn)) {
    player.vx = 0;
  }
}

void update() {
  Player::update();
  // Levels::update();

}

void draw() {
  // draw player
  // Sprites::drawSelfMasked(player.x, player.y, player.sprite, player.frame);
  Sprites::drawSelfMasked(SCREENMID, player.y, player.sprite, player.frame);



  // draw level
  Level::drawLevel();
  arduboy.setCursor(8, 8);
  arduboy.print(player.x);

}



}
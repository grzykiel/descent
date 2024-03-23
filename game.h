#include "controls.h"
#include "player.h"

namespace Game
{
  void loop();
  void input();
  void update();
  void draw();

  void loop() 
  {
    input();
    update();
    draw();
  }

  void input() 
  {
    if (arduboy.justPressed(left_btn))
    {
      player.dir = Direction::left;
    }
    else if (arduboy.justPressed(right_btn))
    {
      player.dir = Direction::right;
    }

    if (arduboy.pressed(left_btn))
    {
      player.vy = -walkSpeed;
    }
    else if (arduboy.pressed(right_btn))
    {
      player.vy = walkSpeed;
    }
    else if (arduboy.notPressed(left_btn | right_btn))
    {
      player.vy = 0;
    }
  }

  void update() {
    playerNext.y = player.y + player.vy;
    // TODO collision check
    player.y = playerNext.y;
  }

  void draw() {
    arduboy.setCursor(52, 32);
    if (player.dir == Direction::left)
    {
      Sprites::drawSelfMasked(player.x, player.y, Player::runLeftSprite, 0);
    }
    else if (player.dir == Direction::right)
    {
      Sprites::drawSelfMasked(player.x, player.y, Player::runRightSprite, 0);
    }

  }
}

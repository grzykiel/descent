#include "game.h"
#include "levels.h"
#include "player.h"
#include "bitmaps.h"

namespace Game
{
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
      player.sprite = Player::runLeftSprite;
    }
    else if (arduboy.justPressed(right_btn))
    {
      player.dir = Direction::right;
      player.sprite = Player::runRightSprite;
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

    if (arduboy.pressed(up_btn))
    {
      player.vx = walkSpeed;
    }
    else if (arduboy.pressed(down_btn))
    {
      player.vx = -walkSpeed;
    }
    else if (arduboy.notPressed(up_btn|down_btn)) 
    {
      player.vx = 0;
    }
  }

  void update() 
  {
    Player::update();
    // collisionCheck();
  }

  void draw() {
    // draw player
    Sprites::drawSelfMasked(player.x, player.y, player.sprite, player.frame);



    // draw level
    Level::drawLevel();

  }

  void collisionCheck() 
  {
    int yMin = int (player.y/BLOCKSIZE);
    int yMax = yMin + 1;

    int xMin = SCREENHEIGHT - 2 - ceil(player.x/BLOCKSIZE);
    int xMax = xMin + 1;


    for (int i = xMin; i <= xMax; i++) 
    {
      for (int j = yMin; j <= yMax; j++) 
      {
        // Sprites::drawSelfMasked((SCREENHEIGHT - i - 1) * BLOCKSIZE, j * BLOCKSIZE, Tiles::block, sandbox[i][j]);
        if (sandbox[i][j]) 
        {

          Rect blockRect = Rect((SCREENHEIGHT - i -1) * BLOCKSIZE, j * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
          // adjust horizontal
          Rect playerRect = Rect(player.x, playerNext.y, BLOCKSIZE, BLOCKSIZE);
          if (arduboy.collide(blockRect, playerRect)) 
          {
            if (blockRect.y < playerNext.y) {
              playerNext.y = blockRect.y + BLOCKSIZE;
            }
          }
        }
      }
    }
  }

  /*vector collisionCorrect(Rect currentRect, Rect nextRect, Rect collisionRect)
  {
    vector v;
    return v;
  }*/

}
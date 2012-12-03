#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

block::block()
{
  srand ( time(NULL) );
  number = rand() % 6 + 1;
  p_xp = 224;
  p_yp = 64;
  block_spr.setPosition(p_xp-48,p_yp);
  block_rect = sf::Rect<float>(p_xp, p_yp, 16, 16);
  speed=.07;
}

block::block(int n)
{
  number = n;
  p_xp = 224;
  p_yp = 64;
  block_spr.setPosition(p_xp,p_yp);
  block_rect = sf::Rect<float>(p_xp, p_yp, 16, 16);
  speed=.07;
}

sf::Sprite& block:: get_sprite()
{
  return block_spr;
}

sf::Rect<float>& block:: get_rect()
{
  return block_rect;
}

void block:: set_x(double xp)
{
  p_xp = xp;
  block_spr.setPosition(p_xp, p_yp);
  block_rect = sf::Rect<float>(p_xp, p_yp, 16, 16);
}

void block:: set_y(double yp)
{
  p_yp = yp;
  block_spr.setPosition(p_xp, p_yp);
  block_rect = sf::Rect<float>(p_xp, p_yp, 16, 16);
}

double block:: get_y()
{
  return p_yp;
}

double block:: get_x()
{
  return p_xp;
}

int block:: get_number()
{
  return number;
}

void block:: set_number(int n)
{
  number = n;
}

void block:: set_top(bool t)
{
  top = t;
}

double block:: get_speed()
{
  return speed;
}

void block:: set_speed(double s)
{
  speed = s;
}

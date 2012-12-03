#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

class block
{
  private:
    sf::Sprite block_spr;
    sf::Rect<float> block_rect;
    double p_xp;
    double p_yp;
    int number;
    bool top;
    double speed;

  public:
    block();
    block(int n);
    sf::Sprite& get_sprite();
    sf::Rect<float>& get_rect();
    void set_x(double xp);
    void set_y(double yp);
    double get_y();
    double get_x();
    int get_number();
    void set_number(int n);
    void set_top(bool t);
    double get_speed();
    void set_speed(double s);
};

#endif

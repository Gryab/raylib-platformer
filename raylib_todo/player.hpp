#ifndef PLAYER_H
#define PLAYER_H

#include "Level.hpp"
#include "raylib.h"
#include "common_defines.h"
#include "Collision_box.hpp"

class Player : public Collision_box
{

  private:

    u8 r, g, b;

  public: 

    Vector2 velocity;
    Vector2 acceleration;

    Color line_color;

    void update_rainbow(void);

    void draw(void);

    void move(void);

    void collide(void);

    void controls(void);

    void update(const Level& level);

    Player(Rectangle player_rect, Vector2 v, Vector2 a, const Color& color);

};

#endif

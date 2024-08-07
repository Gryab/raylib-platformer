#ifndef PLAYER_H
#define PLAYER_H

#include "Collision_box.hpp"
#include "Level.hpp"
#include "common_defines.h"
#include "raylib.h"
#include "raymath.h"

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

    void spawn_on_level(const Level& level);

    void check_finish(const Level& level);

    Player(Rectangle player_rect, Vector2 v, Vector2 a, const Color& color);

};

#endif

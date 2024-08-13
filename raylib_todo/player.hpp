#ifndef PLAYER_H
#define PLAYER_H

#include "Collision_box.hpp"
#include "common_defines.h"
#include "raylib.h"
#include "raymath.h"

class Player : public Collision_box
{

  private:

    u8 r, g, b;

  public: 

    bool paused = false;

    Vector2 velocity;
    Vector2 acceleration;

    Color line_color;

    void update_rainbow(void);

    void draw(void) const;

    void move(void);

    void collide(void);

    void controls(void);

    void update(const Level& level);

    void spawn_on_level(const Level& level);

    bool check_finish(const Level& level) const;

    Player(Rectangle player_rect, Vector2 v, Vector2 a, const Color& color);

};

#endif

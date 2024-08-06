#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "common_defines.h"
#include "raylib.h"
#include "Level.hpp"

typedef enum {TOP = 0, RIGHT = 1, BOTTOM = 2, LEFT = 3} collision_rect_direction;

typedef union 
{
  struct {
    bool top;
    bool right;
    bool bottom;
    bool left;
  };
  u32 as_bitfield;

} collision_directions;

class Collision_box 
{

  protected:

    Rectangle rect;

    const Rectangle* collides_with[4] = {new Rectangle{0}, new Rectangle{0}, new Rectangle{0}, new Rectangle{0}};

  public: 
    collision_directions collisions = {0};

    r32 &x_pos = rect.x;
    r32 &y_pos = rect.y;
    r32 &width = rect.width;
    r32 &height = rect.height;
    Vector2 &pos = *(Vector2*)&rect;

    void check_collision(const Level& level);

    bool top_check_line_collision(Rectangle rec);
    
    bool right_check_line_collision(Rectangle rec);
    
    bool bottom_check_line_collision(Rectangle rec);
    
    bool left_check_line_collision(Rectangle rec);

    Collision_box(Rectangle player_rect);

    ~Collision_box(void);

};

#endif

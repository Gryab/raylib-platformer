#include "Collision_box.h"
#include "common_defines.h"
#include "raylib.h"
#include <iostream>

Collision_box::Collision_box(Rectangle rec) : rect(rec){return;};

void Collision_box::check_collision(const Level& level)
{
  std::cout << "collision check\n";
  for(u32 i = 0; i < level.rects.size(); ++i)
  {

    if(top_check_line_collision(level.rects.at(i)))
    {
      collisions.top = true;
      collides_with[TOP] = &level.rects.at(i);
    }else if (!top_check_line_collision(*collides_with[TOP])) {
      collisions.top = false;
    }
    
    if(right_check_line_collision(level.rects.at(i)))
    {
      collisions.right = true;
      collides_with[RIGHT] = &level.rects.at(i);
    }else if(!right_check_line_collision(*collides_with[RIGHT])){
      collisions.right = false;
    }
    
    if(bottom_check_line_collision(level.rects.at(i)))
    {
      collisions.bottom = true;
      collides_with[BOTTOM] = &level.rects.at(i);
    }else if (!bottom_check_line_collision(*collides_with[BOTTOM])) {
      collisions.bottom = false;
    }
    
    if(left_check_line_collision(level.rects.at(i)))
    {
      collisions.left = true;
      collides_with[LEFT] = &level.rects.at(i);
    }else if (left_check_line_collision(*collides_with[LEFT])) {
      collisions.left = false;
    }
  }
}

bool Collision_box::right_check_line_collision(Rectangle rec)
{
  return CheckCollisionPointRec(Vector2{(r32)x_pos + width + 1.0f, (r32)y_pos + height/2.0f}, rec);
}

bool Collision_box::bottom_check_line_collision(Rectangle rec)
{
  return CheckCollisionPointRec(Vector2{(r32)x_pos + width/2.0f, y_pos + height + 1.0f}, rec);
}

bool Collision_box::left_check_line_collision(Rectangle rec)
{
  return CheckCollisionPointRec(Vector2{(r32)x_pos - 1.0f, (r32)(y_pos + height / 2.0f)}, rec);
}

bool Collision_box::top_check_line_collision(Rectangle rec)
{
  return CheckCollisionPointRec(Vector2{(r32)(x_pos + width / 2.0f), (r32)y_pos - 1.0f}, rec);
}

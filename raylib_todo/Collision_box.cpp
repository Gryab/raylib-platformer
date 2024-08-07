#include "Collision_box.hpp"

Collision_box::Collision_box(const Rectangle &rec) : rect(rec){};

void Collision_box::check_collision(const Level& level)
{
  for (u32 i = 0; i < level.rects.size(); ++i)
  {

    if (top_check_line_collision(level.rects.at(i)))
    {
      collisions.top = true;
      collides_with[TOP] = &level.rects.at(i);
      continue;
    }
    else if (!top_check_line_collision(*collides_with[TOP])) 
    {
      collisions.top = false;
    }
    
    if (bottom_check_line_collision(level.rects.at(i)))
    {
      collisions.bottom = true;
      collides_with[BOTTOM] = &level.rects.at(i);
      continue;
    }
    else if (!bottom_check_line_collision(*collides_with[BOTTOM]))
    {
      collisions.bottom = false;
    }
    
    if (right_check_line_collision(level.rects.at(i)))
    {
      collisions.right = true;
      collides_with[RIGHT] = &level.rects.at(i);
      continue;
    }
    else if (!right_check_line_collision(*collides_with[RIGHT]))
    {
      collisions.right = false;
    }
    
    if (left_check_line_collision(level.rects.at(i)))
    {
      collisions.left = true;
      collides_with[LEFT] = &level.rects.at(i);
      continue;
    }
    else if (!left_check_line_collision(*collides_with[LEFT]))
    {
      collisions.left = false;
    }
  }
}

bool Collision_box::right_check_line_collision(Rectangle rec)
{
  return CheckCollisionRecs(Rectangle{x_pos + width - 1.0f, y_pos, 1.0f, height}, rec);
}

bool Collision_box::bottom_check_line_collision(Rectangle rec)
{
  return CheckCollisionRecs(Rectangle{x_pos, y_pos + height, width, 1.0f}, rec);
}

bool Collision_box::left_check_line_collision(Rectangle rec)
{
  return CheckCollisionRecs(Rectangle{x_pos - 1.0f, y_pos, 1.0f, height}, rec);
}

bool Collision_box::top_check_line_collision(Rectangle rec)
{
  return CheckCollisionRecs(Rectangle{x_pos, y_pos - 1.0f, width, 1.0f}, rec);
}

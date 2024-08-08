#include "player.hpp"
#include "raylib.h"
#include <cstdlib>

Player::Player(Rectangle player_rect, Vector2 v, Vector2 a, const Color& color) : Collision_box(player_rect), velocity(v), acceleration(a)
{

  this->r = color.r, this->g = color.g, this->b = color.b, this->line_color.a = color.a;

}

void Player::draw(void) const
{

  DrawRectangleRec(this->rect, BLACK);
  DrawRectangleLinesEx(this->rect, MIN_COLLISION_LENGTH / 2.0f, this->line_color);

}

void Player::update_rainbow(void)
{ 

  line_color = {(u8)(128 + (r >> 1)), (u8)(128 + (g >> 1)), (u8)(128 + (b >> 1)), 255};
  
  if((r > 0) * !b)
  {
    r--;
    g++;
    return;
  }
  if((g > 0) * !r)
  {
    g--;
    b++;
    return;
  }
  if((b > 0) * !g)
  {
    b--;
    r++;
    return;
  }

}

void Player::controls(void)
{

  if(IsKeyDown(KEY_SPACE))
  {
    if(collisions.bottom){
      velocity.y = -5.0f;
    }
    if(collisions.top){
      velocity.y = 5.0f;
    }
  }
}

void Player::move(void)
{
  r32 frame_time = GetFrameTime();
  x_pos += velocity.x;
  y_pos += velocity.y;
  velocity.x += acceleration.x * frame_time;
  velocity.y += acceleration.y * frame_time;

}

void Player::collide(void){

  if(collisions.top)
  {
    y_pos = collides_with[TOP]->y + collides_with[TOP]->height;
    velocity.y = 0;
  }

  if(collisions.right)
  {
    x_pos = collides_with[RIGHT]->x - width;
    velocity.x = -velocity.x;
  }

  if(collisions.bottom)
  {
    velocity.y = 0;
    y_pos = collides_with[BOTTOM]->y - height;
  }

  if(collisions.left)
  {
    x_pos = collides_with[LEFT]->x + collides_with[LEFT]->width;
    velocity.x = -velocity.x;
  }
}

bool Player::check_finish(const Level& level) const
{
  return CheckCollisionRecs(level.finish, rect);
}

void Player::spawn_on_level(const Level& level)
{

  pos = level.start;

}

void Player::update(const Level& level)
{

  update_rainbow();
  controls();
  move();
  check_collision(level);
  check_finish(level);
  collide();

}

#include "player.h"
#include "Collision_box.h"
#include "Level.h"
#include "common_defines.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

Player::Player(Rectangle player_rect, Vector2 v, Vector2 a, const Color& color) : Collision_box(player_rect), velocity(v), acceleration(a)
{

  this->r = color.r, this->g = color.g, this->b = color.b, this->line_color.a = color.a;

  return;
}

void Player::draw(void)
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

/*
void Player::jump(float amount){
  velocity.y = -5.0f;
}
*/
void Player::controls(void)
{

  if(IsKeyDown(KEY_SPACE))
  {
    if(collisions.bottom){
      velocity.y = -5.0f;
      collisions.bottom = false;
    }
    if(collisions.top){
      velocity.y = 5.0f;
      collisions.top = false;
    }
  }

  if(IsKeyDown(KEY_D))
  {
    velocity.x = PLAYER_SPEED;
    collisions.left = false;
  }
  if(IsKeyDown(KEY_A))
  {
    velocity.x = -PLAYER_SPEED;
    collisions.right = false;
  }
#ifdef DEBUG
  if(IsKeyDown(KEY_W))
  {
    velocity.y = -PLAYER_SPEED;
    collisions.bottom = false;
  }
  if(IsKeyUp(KEY_W))
  {
    velocity.y = 0.0f;
  }

  if(IsKeyDown(KEY_S))
  {
    velocity.y = PLAYER_SPEED;
    collisions.top = false;
  }
  if(IsKeyUp(KEY_S) * IsKeyUp(KEY_W))
  {
    velocity.y = 0.0f;
  }
#endif
}

void Player::move(void)
{

  pos = Vector2Add(pos, velocity);
  velocity.x += acceleration.x * GetFrameTime();
  velocity.y += acceleration.y * GetFrameTime();

}

void Player::collide(void){

  if(collisions.top)
  {
    std::cout << "top\n";
    y_pos = collides_with[TOP]->y + collides_with[TOP]->height;
    velocity.y = 0;
  }

  if(collisions.right)
  {
    std::cout << "right\n";
    velocity.x = -velocity.x;
    x_pos = collides_with[RIGHT]->x - width;
  }

  if(collisions.bottom)
  {
    velocity.y = 0;
    y_pos = collides_with[BOTTOM]->y - height;
    
    if(velocity.x > 0.0f)
    {
      velocity.x -= 0.05f * acceleration.y;
    }
    else if(velocity.x < 0.0f)
    {
      velocity.x += 0.05f * acceleration.y;
    }
  }

  if(collisions.left)
  {
    std::cout << "left\n";
    x_pos = collides_with[LEFT]->x + collides_with[LEFT]->width;
    velocity.x = -velocity.x;
  }
}

void Player::update(const Level& level)
{

  update_rainbow();
  controls();
  move();
  check_collision(level);
  collide();

}

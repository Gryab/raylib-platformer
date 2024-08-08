#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include "player.hpp"
#include "Level.hpp"
#include <string>

std::vector<std::string> level_names = {"level1", "level2", "end_level"};
u8 level_name_num = 0;

r32 player_size = MIN_COLLISION_LENGTH * 5.0f;
Vector2 velocity = {PLAYER_SPEED, 0.0f};
Vector2 g = {0.0f, 10.0f};

Level level;

s32 LoopUpdate(Player& player);

s32 StartGame(void);

s32 HandleFinish(const Player& player);

int main() 
{ 

  StartGame();

	return 0;
}

s32 StartGame(void)
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");

  level.load(level_names.at(level_name_num));

  Player player(Rectangle{20.0f, 20.0f, player_size, player_size}, velocity, g, Color{255, 0, 0});

  player.spawn_on_level(level);

  SetTargetFPS(75);

  while (!WindowShouldClose())
  {
    LoopUpdate(player);
  };

	CloseWindow();

  return 0;
}

s32 HandleFinish(Player& player)
{

  if (++level_name_num >= level_names.size() - 1) player.acceleration = {0}, player.velocity.y = 0.0f;
  
  level.load(level_names.at(level_name_num));
  player.spawn_on_level(level);
  
  return 0;

}

s32 LoopUpdate(Player& player)
{

  if(player.y_pos >= SCREEN_HEIGHT) player.spawn_on_level(level);

  player.update(level);

  if (player.check_finish(level)) HandleFinish(player);

  BeginDrawing();

    ClearBackground(RAYWHITE);
    
    level.draw();
    
    player.draw();
    
    DrawFPS(10, 10);

  EndDrawing();

  return 0;
}

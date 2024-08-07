#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include "player.hpp"
#include "Level.hpp"
#include <string>

r32 player_size = MIN_COLLISION_LENGTH * 5.0f;
Vector2 velocity = {5.0f, 0.0f};
Vector2 g = {0.0f, 10.0f};

Level level;

s32 LoopUpdate(Player& player);

s32 StartGame(void);

int main() 
{ 

  StartGame();

	return 0;
}

s32 StartGame(void)
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");

  level.load("level");

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

s32 LoopUpdate(Player& player)
{

  player.update(level);

  BeginDrawing();

    ClearBackground(RAYWHITE);
    
    level.draw();
    
    player.draw();
    
    DrawFPS(10, 10);

  EndDrawing();

  return 0;
}

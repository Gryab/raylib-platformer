#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include "player.h"
#include "Level.h"
#include <string>

r32 player_size = MIN_COLLISION_LENGTH * 5.0f;
Vector2 velocity = {0.0f, 0.0f};
Vector2 g = {0.0f, 10.0f};

Level level;

s32 LoopUpdate(void);

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

  SetTargetFPS(75);

  while(!WindowShouldClose())
  {
    LoopUpdate();
  };

	CloseWindow();

  return 0;
}

s32 LoopUpdate(void)
{

  static Player player(Rectangle{ 20.0f, 20.0f, player_size, player_size}, velocity, g, Color{255, 0, 0});

  if(IsKeyPressed(KEY_R))
  {
    level.load("level");
  }

  player.update(level);

  BeginDrawing();

    ClearBackground(RAYWHITE);
    
    level.draw();
    
    player.draw();
    
    DrawFPS(10, 10);

  EndDrawing();

  return 0;
}

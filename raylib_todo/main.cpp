#include "config.hpp"
#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include "player.hpp"
#include "Level.hpp"
#include <ios>
#include <string>

namespace game 
{

  std::vector<std::string> level_names;
  u32 level_name_num = 0;

  bool ended = false;
  std::string final_time;

  r32 player_size = MIN_COLLISION_LENGTH * 5.0f;
  Vector2 velocity = {PLAYER_SPEED, 0.0f};
  Vector2 g = {0.0f, 10.0f};

  Level level;

  r32 timer;

  Texture2D background_texture;

}

s32 LoadLevelList(void);

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

  s32 return_value = 0;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");

  if(LoadLevelList() != 0) 
  {
    return_defer(1);
  }

  {

    Image background_image = LoadImage("assets/background.png");

    game::background_texture = LoadTextureFromImage(background_image);

    game::level.load(game::level_names.at(game::level_name_num));

    Player player(Rectangle{20.0f, 20.0f, game::player_size, game::player_size}, game::velocity, game::g, Color{255, 0, 0, 255});

    player.spawn_on_level(game::level);

    SetTargetFPS(75);

    while (!WindowShouldClose())
    {
      LoopUpdate(player);
    }


    UnloadImage(background_image);

    UnloadTexture(game::background_texture);
  }
defer:

  CloseWindow();

  return return_value;
}

void HandleWin(Player& player)
{

  player.acceleration = {0};
  player.velocity.y = 0.0f;
  player.velocity.x /= 2.0f;

  game::ended = true;

  game::final_time = std::to_string(game::timer);
  game::final_time += " seconds";

}

s32 HandleFinish(Player& player)
{

  if (++game::level_name_num >= game::level_names.size() - 1) HandleWin(player);
  
  game::level.load(game::level_names.at(game::level_name_num));
  player.spawn_on_level(game::level);

  return 0;

}

void DrawEndScreen(const Player& player)
{

  DrawText("Final time:", (s32)(player.x_pos/2.0f + SCREEN_WIDTH/16.0f), (s32)(player.y_pos - 50.0f), 50, Color{player.line_color.b, 128, player.line_color.r, 255});
  
  DrawText(game::final_time.c_str(), (s32)(player.x_pos/3.0f + SCREEN_WIDTH/8.0f), (s32)(player.y_pos + 50.0f), 50, Color{player.line_color.r, 128, player.line_color.g, 255});

}

s32 LoopUpdate(Player& player)
{

  if(player.y_pos >= SCREEN_HEIGHT) player.spawn_on_level(game::level);

  if(IsKeyPressed(KEY_R)) game::level.load(game::level_names.at(game::level_name_num)), player.spawn_on_level(game::level);

  player.update(game::level);

  if (player.check_finish(game::level)) HandleFinish(player);

  BeginDrawing();

    DrawTexture(game::background_texture, 0, 0, Color{255, 255, 255, 255});
    
    game::level.draw();
    
    player.draw();

    if(game::ended) DrawEndScreen(player);
    
    DrawFPS(10, 10);

  EndDrawing();

  game::timer += GetFrameTime();

  return 0;
}

s32 LoadLevelList(void)
{

  std::fstream file;
  file.open("level_list.txt", std::ios_base::in | std::ios_base::binary);

  if(!file.is_open()) return 1;
  
  std::string level_name;

  char clevel_name[100];

  while (file.getline(clevel_name, 100, ';').good()) 
  {
    level_name = clevel_name;
    game::level_names.push_back(level_name.substr(level_name.find_first_not_of(' ')));
  }

  while (file.is_open())
  {
    file.close();
  }
  return 0;

}

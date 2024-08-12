#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include "player.hpp"
#include "Level.hpp"
#include <ios>
#include <string>

namespace config 
{

  #include "Menu.c" //i can explain, trust me

}

typedef enum 
{

  NO_SCREEN = 0,
  MENU_SCREEN = 1,
  LEVEL_SCREEN = 2

} screen_enum;

namespace game 
{

  screen_enum current_screen = NO_SCREEN;

  std::vector<std::string> level_names;
  u32 level_name_num;

  bool ended;
  std::string final_time;

  r32 player_size;
  Vector2 velocity;
  Vector2 g;

  Level level;

  r32 timer;

  Texture2D sun_texture, clowds0, over0, over1, over2, over3, over4;

}

s32 LoadLevelList(void);

s32 GameLoopUpdate(Player& player);

s32 StartGame(void);

s32 HandleFinish(const Player& player);

void InitValues(void);

int main() 
{ 

  StartGame();

	return 0;
}

s32 StartGame(void)
{

  s32 return_value = 0;

  InitValues();

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");
  
  SetTargetFPS(75);

  if(LoadLevelList() != 0) 
  {
    return_defer(1);
  }

  {
    {
      Image _image = LoadImage("assets/SUN.png");
      game::sun_texture = LoadTextureFromImage(_image);
      _image = LoadImage("assets/CLOWDS0.png");
      game::clowds0 = LoadTextureFromImage(_image);
      _image = LoadImage("assets/over0.png");
      game::over0 = LoadTextureFromImage(_image);
      _image = LoadImage("assets/over1.png");
      game::over1 = LoadTextureFromImage(_image);
      _image = LoadImage("assets/over2.png");
      game::over2 = LoadTextureFromImage(_image);
      _image = LoadImage("assets/over3.png");
      game::over3 = LoadTextureFromImage(_image);
      _image = LoadImage("assets/over4.png");
      game::over4 = LoadTextureFromImage(_image);
      UnloadImage(_image);
    }
    game::level.load(game::level_names.at(game::level_name_num));

    Player player(Rectangle{20.0f, 20.0f, game::player_size, game::player_size}, game::velocity, game::g, Color{255, 0, 0, 255});

    player.spawn_on_level(game::level);

    while (!WindowShouldClose())
    {
      switch (game::current_screen)
      {
        
        case NO_SCREEN: 
        {
          return_defer(1);
        }
        break;

        case MENU_SCREEN:
        {
          config::UpdateMenu();
        }
        break;

        case LEVEL_SCREEN:
        {
          GameLoopUpdate(player);
        }
        break;

        default: 
        {
          return_defer(1);
        }
        break;

      }

    }

    UnloadTexture(game::sun_texture);
    UnloadTexture(game::clowds0);
    UnloadTexture(game::over0);
    UnloadTexture(game::over1);
    UnloadTexture(game::over2);
    UnloadTexture(game::over3);
    UnloadTexture(game::over4);
  }
defer:

  CloseWindow();

  return return_value;
}

void InitValues(void)
{

  game::current_screen = MENU_SCREEN;

  game::level_name_num = 0;

  game::ended = false;

  game::player_size = MIN_COLLISION_LENGTH * 5.0f;
  
  game::velocity = {PLAYER_SPEED, 0.0f};
  
  game::g = {0.0f, 10.0f};

}

s32 RestartGame(Player& player)
{

  InitValues();

  game::level.load(game::level_names.at(game::level_name_num));

  player.velocity = game::velocity;
  
  player.acceleration = game::g;

  player.spawn_on_level(game::level);
  
  return 0;
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

s32 GameLoopUpdate(Player& player)
{

  if(player.y_pos >= SCREEN_HEIGHT) player.spawn_on_level(game::level);

  if(IsKeyPressed(KEY_R)) game::level.load(game::level_names.at(game::level_name_num)), player.spawn_on_level(game::level);

  if(game::ended & IsKeyPressed(KEY_ENTER)) RestartGame(player);

  player.update(game::level);

  if (player.check_finish(game::level)) HandleFinish(player);

  BeginDrawing();
    
    ClearBackground(LIGHT_BASE_COLOR);

    DrawTextureEx(game::sun_texture, Vector2{0 - player.x_pos / 32.0f, 0 - player.y_pos / 32.0f}, 0.0f, 1.0f, LIGHT_GOLD_COLOR);

    DrawTextureEx(game::clowds0, Vector2{0 - player.x_pos / 25.0f, 0 - player.y_pos / 25.0f}, 0.0f, 1.0f, ColorAlpha(LIGHT_RED_SUBTLE_COLOR, 0.5f));
    
    DrawTextureEx(game::over0, Vector2{0 - player.x_pos / 20.0f, 0 - player.y_pos / 20.0f}, 0.0f, 0.75f, LIGHT_BASE_DARKER_COLOR);
    DrawTextureEx(game::over1, Vector2{0 - player.x_pos / 8.0f, 0 - player.y_pos / 8.0f}, 0.0f, 0.75f, LIGHT_HIGH_MID_COLOR);
    DrawTextureEx(game::over2, Vector2{0 - player.x_pos / 4.0f, 0 - player.y_pos / 4.0f}, 0.0f, 0.75f, LIGHT_HIGH_HIGH_COLOR);
    DrawTextureEx(game::over3, Vector2{0 - player.x_pos / 3.5f, 0 - player.y_pos / 3.5f}, 0.0f, 0.75f, LIGHT_MAIN_HALF_COLOR);
    DrawTextureEx(game::over4, Vector2{0 - player.x_pos / 3.0f, 0 - player.y_pos / 3.0f}, 0.0f, 0.7f, LIGHT_MAIN_TWO_THIRDS_COLOR);

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

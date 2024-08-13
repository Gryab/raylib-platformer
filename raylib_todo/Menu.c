#include "common_defines.h"
#include "config.h"
#include "raylib.h"
#ifndef MENU_C            //yes, an include guard in a .c file 
#define MENU_C

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{

  NO_SCREEN = 0,
  MENU_SCREEN = 1,
  LEVEL_SCREEN = 2

} screen_enum;

typedef enum 
{
  NO_OPTION = 0,

  QUIT = 1,

  THEME_TOGGLE = 2,

} menu_options;

typedef enum 
{ 
  
  LIGHT = 0,

  DARK = 1,

} theme;

theme current_theme = DARK;

screen_enum current_screen = NO_SCREEN;

void handle_nothing(void)
{
  return;
}

void handle_quit(void) 
{
  running = false;
}

void handle_theme(void)
{
  current_theme = (current_theme == LIGHT) ? DARK : LIGHT;
  if(current_theme == LIGHT)
  {
    MAIN_FULL_COLOR       = LIGHT_MAIN_FULL_COLOR;         
    MAIN_TWO_THIRDS_COLOR = LIGHT_MAIN_TWO_THIRDS_COLOR;
    MAIN_HALF_COLOR       = LIGHT_MAIN_HALF_COLOR;      
    BASE_COLOR            = LIGHT_BASE_COLOR;           
    BASE_LIGHTER_COLOR    = LIGHT_BASE_LIGHTER_COLOR;   
    BASE_DARKER_COLOR     = LIGHT_BASE_DARKER_COLOR;    
    RED_BRIGHT_COLOR      = LIGHT_RED_BRIGHT_COLOR;     
    RED_SUBTLE_COLOR      = LIGHT_RED_SUBTLE_COLOR;     
    GOLD_COLOR            = LIGHT_GOLD_COLOR;           
    YELLOW_COLOR          = LIGHT_YELLOW_COLOR;         
    FINISH_COLOR          = LIGHT_FINISH_COLOR;         
    FINISH_DARK_COLOR     = LIGHT_FINISH_DARK_COLOR;    
    PURPLE_COLOR          = LIGHT_PURPLE_COLOR;         
    HIGH_LOW_COLOR        = LIGHT_HIGH_LOW_COLOR;       
    HIGH_MID_COLOR        = LIGHT_HIGH_MID_COLOR;       
    HIGH_HIGH_COLOR       = LIGHT_HIGH_HIGH_COLOR;      
  } else if(current_theme == DARK)
  {
    MAIN_FULL_COLOR       = DARK_MAIN_FULL_COLOR;      
    MAIN_TWO_THIRDS_COLOR = DARK_MAIN_TWO_THIRDS_COLOR;
    MAIN_HALF_COLOR       = DARK_MAIN_HALF_COLOR;      
    BASE_COLOR            = DARK_BASE_COLOR;           
    BASE_LIGHTER_COLOR    = DARK_BASE_LIGHTER_COLOR;   
    BASE_DARKER_COLOR     = DARK_BASE_DARKER_COLOR;    
    RED_BRIGHT_COLOR      = DARK_RED_BRIGHT_COLOR;     
    RED_SUBTLE_COLOR      = DARK_RED_SUBTLE_COLOR;     
    GOLD_COLOR            = DARK_GOLD_COLOR;           
    YELLOW_COLOR          = DARK_YELLOW_COLOR;         
    FINISH_COLOR          = DARK_FINISH_COLOR;         
    FINISH_DARK_COLOR     = DARK_FINISH_DARK_COLOR;    
    PURPLE_COLOR          = DARK_PURPLE_COLOR;         
    HIGH_LOW_COLOR        = DARK_HIGH_LOW_COLOR;       
    HIGH_MID_COLOR        = DARK_HIGH_MID_COLOR;       
    HIGH_HIGH_COLOR       = DARK_HIGH_HIGH_COLOR;      
  }
}

struct {s32 selected_option; char* menu_options[THEME_TOGGLE + 1]; void(*handle_menu_item[THEME_TOGGLE + 1])(void);} Menu = {QUIT, \
                                                                                                                            {"NOTHING", "QUIT", "Change theme"}, \
                                                                                                                            {handle_nothing, handle_quit, handle_theme}};
void DrawMenu(void)
{

  static Rectangle nothing_menu_item_rect = {SCREEN_WIDTH / 2.0f - MIN_COLLISION_LENGTH * 50.0f / 2.0f, \
                                          SCREEN_HEIGHT / 2.0f - MIN_COLLISION_LENGTH * 4.0f, \
                                          MIN_COLLISION_LENGTH * 50.0f, \
                                          MIN_COLLISION_LENGTH * 4.0f};
  Color nothing_menu_item_color = (Menu.selected_option == NO_OPTION)? Color{0, 0, 0, 0} : BASE_LIGHTER_COLOR;
  
  static Rectangle quit_menu_item_rect = {SCREEN_WIDTH / 2.0f - MIN_COLLISION_LENGTH * 50.0f / 2.0f, \
                                          SCREEN_HEIGHT / 2.0f, \
                                          MIN_COLLISION_LENGTH * 50.0f, \
                                          MIN_COLLISION_LENGTH * 4.0f};
  Color quit_menu_item_color = (Menu.selected_option == QUIT)? Color{0, 0, 0, 0} : BASE_LIGHTER_COLOR;
  
  static Rectangle theme_menu_item_rect =  {SCREEN_WIDTH / 2.0f - MIN_COLLISION_LENGTH * 50.0f / 2.0f, \
                                            SCREEN_HEIGHT / 2.0f + MIN_COLLISION_LENGTH * 4.0f, \
                                            MIN_COLLISION_LENGTH * 50.0f, \
                                            MIN_COLLISION_LENGTH * 4.0f};
  Color theme_menu_item_color = (Menu.selected_option == THEME_TOGGLE)? Color{0, 0, 0, 0} : BASE_LIGHTER_COLOR;

  BeginDrawing();
  {
    
    ClearBackground(BASE_COLOR);
    
    DrawTextureEx(sun_texture, Vector2{0, 0}, 0.0f, 1.0f, GOLD_COLOR);

    DrawTextureEx(clowds0, Vector2{0, 0}, 0.0f, 1.0f, ColorAlpha(RED_SUBTLE_COLOR, 0.5f));
    
    DrawTextureEx(over0, Vector2{0, 0}, 0.0f, 0.75f, BASE_DARKER_COLOR);
    DrawTextureEx(over1, Vector2{0, 0}, 0.0f, 0.75f, HIGH_MID_COLOR);
    DrawTextureEx(over2, Vector2{0, 0}, 0.0f, 0.75f, HIGH_HIGH_COLOR);
    DrawTextureEx(over3, Vector2{0, 0}, 0.0f, 0.75f, MAIN_HALF_COLOR);
    DrawTextureEx(over4, Vector2{0, 0}, 0.0f, 0.7f,  MAIN_TWO_THIRDS_COLOR);
   
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BASE_DARKER_COLOR, 0.5f));
    
    DrawRectangleRec(nothing_menu_item_rect, nothing_menu_item_color);
    DrawText(Menu.menu_options[NO_OPTION], (s32)nothing_menu_item_rect.x, (s32)nothing_menu_item_rect.y, 40, MAIN_FULL_COLOR);
    
    DrawRectangleRec(quit_menu_item_rect, quit_menu_item_color);
    DrawText(Menu.menu_options[QUIT], (s32)quit_menu_item_rect.x, (s32)quit_menu_item_rect.y, 40, MAIN_FULL_COLOR);
    
    DrawRectangleRec(theme_menu_item_rect, theme_menu_item_color);
    DrawText(Menu.menu_options[THEME_TOGGLE], (s32)theme_menu_item_rect.x, (s32)theme_menu_item_rect.y, 40, MAIN_FULL_COLOR);
    
  }  
  EndDrawing();

}

s32 UpdateMenu()
{

  if (IsKeyPressed(KEY_SPACE)) 
  {
    current_screen = LEVEL_SCREEN;
  }

  if (IsKeyPressed(KEY_DOWN))
  {
    Menu.selected_option += 1;
    if (Menu.selected_option > THEME_TOGGLE) Menu.selected_option = 0;
  }

  if (IsKeyPressed(KEY_UP))
  {
    Menu.selected_option -= 1;
    if (Menu.selected_option < 0) Menu.selected_option = THEME_TOGGLE;
  }

  if(IsKeyPressed(KEY_ENTER))
  {
    Menu.handle_menu_item[Menu.selected_option]();
  }

  DrawMenu();

  return 0;
}

#ifdef __cplusplus
}
#endif

#endif

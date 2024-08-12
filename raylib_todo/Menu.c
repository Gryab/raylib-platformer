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

  NO_OPTION = 0,

  THEME_TOGGLE = 1,

} menu_options;

typedef enum 
{ 
  
  LIGHT = 0,

  DARK = 1,

} theme;

theme current_theme = LIGHT;

void DrawMenu(void)
{

  BeginDrawing();
  {

    ClearBackground(LIGHT_BASE_COLOR);
    
  }  
  EndDrawing();

}

s32 UpdateMenu(void)
{

  static menu_options menu_option = NO_OPTION;

  DrawMenu();

  return 0;
}

#ifdef __cplusplus
}
#endif

#endif

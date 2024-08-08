#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "raylib.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define MIN_COLLISION_LENGTH 10.0f
#define PLAYER_SPEED 5.0f

#define LIGHT

#ifdef LIGHT
  #define MAIN_COLOR CLITERAL(Color){87,82,121,255}
  #define BASE_COLOR CLITERAL(Color){250,244,237,255}
  #define FINISH_COLOR CLITERAL(Color){86,148,159,255}
#endif

#ifdef DARK
  #define MAIN_COLOR CLITERAL(Color){25,23,36,255}
  #define BASE_COLOR CLITERAL(Color){144,140,170,255}
  #define FINISH_COLOR CLITERAL(Color){156,207,216,255}
#endif 

#endif 

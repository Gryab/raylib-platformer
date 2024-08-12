#ifndef LEVEL_H
#define LEVEL_H
#include <cstddef>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"
#include <fstream>
#include <ios>
#include <iostream>
#include "config.h"

class Level
{

  public:

  std::vector<Rectangle>rects;

  Vector2 start = {-1.0f, -1.0f};

  Rectangle finish = {0.0f, 0.0f, 0.0f, 0.0f};

  public: 
    
    Level(void);

    void draw(void);

    s32 load(std::string file_name);

};

#endif

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

class Level
{

  public:

  std::vector<Rectangle>rects;

  Vector2 start = {0};

  Rectangle finish = {0.0f, 0.0f, 0.0f, 0.0f};

  public: 
    
    Level(void);

    void draw(void);

    void load(std::string file_name);

};

#endif

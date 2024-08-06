#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "common_defines.h"

class Level
{

  public:

  std::vector<Rectangle>rects;

  public: 
    
    Level(void);

    void draw(void);

    void load(std::string file_name);

};

#endif

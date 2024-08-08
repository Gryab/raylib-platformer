#include "Level.hpp"

Level::Level(void) {return;}

s32 Level::load(std::string file_name)
{
  start = {-1.0f, -1.0f};
  finish = {-1.0f, -1.0f, 0.0f, 0.0f};
  rects.clear();
  std::fstream file(file_name, std::ios_base::in | std::ios_base::binary);
 
  if(!file.is_open()) return 1;

  const std::size_t row_size = (SCREEN_WIDTH / (std::size_t)MIN_COLLISION_LENGTH);

  char row[row_size + 1];
  row[row_size] = '\0';

  for (s32 y = 0; y < SCREEN_HEIGHT / MIN_COLLISION_LENGTH; ++y) 
  {
    file.read(row, row_size);
    //TODO Gryab shitty hack, but works
    file.get();
    file.get();
    for (s32 x = 0; row[x] != '\0'; x++)
    {
      if (row[x] == 'X')
      {
        rects.push_back(Rectangle{(r32)x * MIN_COLLISION_LENGTH, (r32)y * MIN_COLLISION_LENGTH, MIN_COLLISION_LENGTH, MIN_COLLISION_LENGTH});
        for (x++ ; row[x] == 'X'; x++)
        {
          rects.back().width += MIN_COLLISION_LENGTH;
        }
      }
      if (row[x] == 'F') 
      {
        finish = {(r32)x * MIN_COLLISION_LENGTH, (r32)y * MIN_COLLISION_LENGTH, MIN_COLLISION_LENGTH, MIN_COLLISION_LENGTH};
        for (x++; row[x] == 'F'; x++)
        {
          finish.width += MIN_COLLISION_LENGTH;
        }
      }
      if (row[x] == 'S')
      {
        start = {(r32)x * MIN_COLLISION_LENGTH, (r32)y * MIN_COLLISION_LENGTH};
      }
    }
  }

  file.close();
  return 0;
}

void Level::draw(void)
{

  for (u32 i = 0; i < rects.size(); ++i)
  {
    
    DrawRectangleRec(rects.at(i), MAIN_COLOR);

  }

  DrawRectangleRec(finish, FINISH_COLOR);
  
}

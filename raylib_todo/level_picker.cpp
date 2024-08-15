#include <string>
#include <vector>
#include "common_defines.h"
#include <fstream>
#include <Windows.h>
#include "shobjidl_core.h"

s32 ChooseLevel(void)
{
  //TODO GRyab: place all level_list's into level_lists vector using filesystem.hpp or boost (probably boost)
  return 0;
}

std::vector<std::string> LoadLevelList(std::string list_name)
{

  std::fstream file;
  file.open(list_name.c_str(), std::ios_base::in | std::ios_base::binary);

  if(!file.is_open()) return (std::vector<std::string>)1;

  std::vector<std::string> level_names;

  std::string level_name;

  char clevel_name[100];

  while (file.getline(clevel_name, 100, ';').good()) 
  {
    level_name = clevel_name;
    level_names.push_back(level_name.substr(level_name.find_first_not_of(' ')));
  }

  while (file.is_open())
  {
    file.close();
  }
  return level_names;

}

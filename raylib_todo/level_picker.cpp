#include <string>
#include <vector>
#include "common_defines.h"
#include <fstream>
#include <windows.h>
#include <shobjidl.h>

std::string ChooseLevelListOpenFileDialog(void)
{
  
  std::string list_name;
  HRESULT win_result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | \
        COINIT_DISABLE_OLE1DDE);

  if(SUCCEEDED(win_result))
  {

    IFileOpenDialog *open_file_dialog;

    win_result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, 
                  IID_IFileOpenDialog, (void**)&open_file_dialog);

    if(SUCCEEDED(win_result))
    {

      win_result = open_file_dialog->Show(NULL);

      if(SUCCEEDED(win_result))
      {
        
        IShellItem* open_file_dialog_item;

        win_result = open_file_dialog->GetResult(&open_file_dialog_item);

        if(SUCCEEDED(win_result))
        {

          PWSTR cfile_path;
          win_result = open_file_dialog_item->GetDisplayName(SIGDN_FILESYSPATH, &cfile_path);

          if(SUCCEEDED(win_result))
          {
            for(s32 i = 0; cfile_path[i] != '\0'; ++i)
            {
              list_name.push_back((char)cfile_path[i]);
            }
          }
          
          open_file_dialog_item->Release();

        }

      }  

      open_file_dialog->Release();

    }

    CoUninitialize();
  }

  return list_name;

}

std::vector<std::string> FindLevelLists(void)
{
  
  std::vector<std::string> result;
  HANDLE find_handle = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATAA list_file_data;

  find_handle = FindFirstFileA("levels/*.txt", &list_file_data);
  
  if(find_handle == INVALID_HANDLE_VALUE) return result;

  do 
  {
    result.push_back(std::string(list_file_data.cFileName));
  }
  while (FindNextFileA(find_handle, &list_file_data) != 0);

  FindClose(find_handle);

  return result;
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

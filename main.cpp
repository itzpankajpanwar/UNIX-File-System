#include "header.h"
#include "count_name_path.cpp"
#include "normalMode_print.cpp"
#include "commandMode.cpp"
#include "copy_move_rename.cpp"
#include "create_delete.cpp"
#include "goto_search.cpp"
char *root;
 
int main(int argc, char **argv)
{
  if(argc==1) {
      string s=".";
      char *path=new char[s.length()+1];
      strcpy(path,s.c_str());
      root=path;
      openDir(".");
  }
  else if(argc==2){
      root=argv[1];
      openDir(argv[1]);
  }
  // normalMode();
  commandMode();
  return 0;
}
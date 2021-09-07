#include "header.h"
vector<string> d_list;
int tot,win,flag=0,r_sz,c_sz;

int dir_count(const char *path){
  int cnt=0;
  d_list.clear();
  DIR *d;
  struct dirent *dir;
  d=opendir(path);
  if(d){
    while((dir=readdir(d))!=NULL){
      if((string(dir->d_name)=="..") and (strcmp(path,root)==0));
      else{
        d_list.push_back(string(dir->d_name));
        cnt++;
      }
    }
    closedir(d);
  }
  else cout<<"No such directory exists!!";
  return cnt;
}

int file_count(){
    int len;
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
    r_sz=w.ws_row-1;
    c_sz=w.ws_col;
    if(tot<=r_sz) len=tot;
    else len=r_sz;
    return len;
}

void openDir(const char *path){
  DIR *d;
  d=opendir(path);
  d_list.clear();
  tot=dir_count(path);
  int len=file_count();
  sort(d_list.begin(),d_list.end());
  win=0;
  CLEAR;
  CURSOR;
  for(int i=0,itr=1;i<tot and itr<=len;i++,itr++){
    char *temp=new char[d_list[i].length()+1];
    strcpy(temp,d_list[i].c_str());
    print(temp,path);
  }
  CURSOR;
}

int isDir(char *path){
    struct stat s;
    if(stat(path,&s)==-1){
      perror("lstat");
    }
    else{
      if(S_ISDIR(s.st_mode)) return 1;
      else return 0;
    }
    return -1;
}

string file_name(string s){
    string name;
    size_t pos;
    pos=s.find_last_of("/\\");
    name=s.substr(pos+1,s.length());
    return name;
}

void set_back_path(char *path){
    size_t pos;
    string newPath,temp=string(path);
    pos=temp.find_last_of("/\\");
    newPath=temp.substr(0,pos);
    strcpy(c_path,newPath.c_str());
}

void clear_stack(stack<string> &s){
    while(!s.empty()) s.pop();
}

#include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
using namespace std;

#define ESC 27
#define CLEAR printf("\033[2J")
#define CURSOR printf("\033[H");
#define cursor(x,y) printf("\033[%d;%dH",x,y)

extern char *root;
extern char* c_path;
extern int flag;
extern vector<string> d_list;
extern stack<string> back_stack,fwd_stack;
extern int r_sz,c_sz,tot,win;

void openDir(const char *path);
//void nonCanon();
void normalMode();
void print(const char *d_name,const char *root);
int dir_count(const char *path);
int file_count();
int isDir(char *path);
string file_name(string s);
void set_back_path(char *path);
void clear_stack(stack<string> &s);


void input_path(string s);
void next_cmd();
int commandMode();
void copy_cmd(vector<string> args);
void copy_dir(char *path,char *dest);
void copy_file(char* path,char* dest);
void Error(string s);
int startCommandMode();
void del_file(char *path);
void removeFile(vector<string> args);
void del_dir(char* path);
void removeDir(vector<string> args);
void move_cmd(vector<string> args);
void rename_cmd(vector<string> args);
void create_file(vector<string> args);
void create_dir(vector<string> args);
string absPath(string s);
string goto_path(vector<string> args);
bool search(vector<string> args);
void srch(char *path,string f_name);
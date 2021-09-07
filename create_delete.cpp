#include "header.h"

void del_file(char *path){
    int st=remove(path);
    if(st) Error("Error in deleting file");
}
void removeFile(vector<string> args){
    char *path=new char[args[1].length()+1];
    strcpy(path,args[1].c_str());
    del_file(path);
}

void del_dir(char* path){
    DIR *d;
    struct dirent *dir;
    d=opendir(path);
    if(d){
        while((dir=readdir(d))!=NULL){
            if(string(dir->d_name)==".." or string(dir->d_name)==".");
            else{
                string f_path=string(path)+"/"+string(dir->d_name);
                char* s=new char[f_path.length()+1];
                strcpy(s,f_path.c_str());
                struct stat sb;
                if(stat(s,&sb)==-1) perror("lstat");
                else{
                    if(S_ISDIR(sb.st_mode)) del_dir(s);
                    else del_file(s);
                }
            }
        }
        closedir(d);
        int st=rmdir(path);
        if(st==-1) Error("Error in removing directory");
    }            
    else Error("No such directory exists");
}
void removeDir(vector<string> args){
    char *path=new char[args[1].length()+1];
    strcpy(path,args[1].c_str());
    del_dir(path);
}


void create_file(vector<string> args){
    string des=absPath(args[2]);
    string f_name=des+"/"+args[1];
    char *path=new char[f_name.length()+1];
    strcpy(path,f_name.c_str());
    int st=open(path,O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(st==-1) Error("Error in creating new file");
}

void create_dir(vector<string> args){
    string des=absPath(args[2]);
    string f_name=des+"/"+args[1];
    char *path=new char[f_name.length()+1];
    strcpy(path,f_name.c_str());
    //int st=mkdir(path,O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(mkdir(path,0777)==-1) Error("Error in creating new directory");
}
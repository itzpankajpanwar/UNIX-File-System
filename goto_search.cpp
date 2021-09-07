#include "header.h"
//int z=0;
vector<string> res;
string goto_path(vector<string> args){
    return args[1];    
}

void srch(char *path,string f_name){
    struct dirent *dir;
    DIR *d=opendir(path);
    if(d){
        while((dir=readdir(d))!=NULL){
            if((string(dir->d_name)=="..") or (string(dir->d_name)=="."));
            else{
                string name=string(dir->d_name);
                string des=string(path)+"/"+name;
                char *my_path=new char[des.length()+1];
                strcpy(my_path,des.c_str());
                struct stat sb;
                //cout<<name<<"  "<<f_name<<endl;
                if(stat(my_path,&sb)==-1) perror("lstat");
                else{
                    if(S_ISDIR(sb.st_mode)){
                        if(f_name.compare(name)==0) {
                            res.push_back(string(my_path));
                        }
                        srch(my_path,f_name);
                    }
                    else
                    {
                        if(f_name.compare(name)==0){
                            res.push_back(string(my_path));
                        }
                    }
                }
            }
        }
    }
}
bool search(vector<string> args){
    string f_name=args[1];
    //cout<<f_name<<endl;
    //cout<<args[1]<<endl;;
    char *path=new char[strlen(c_path)+1];
    strcpy(path,c_path);
    srch(path,f_name);
    if(res.size()>=1) return true;
    return false;
}

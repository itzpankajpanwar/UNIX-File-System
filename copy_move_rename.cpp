#include "header.h"

void copy_dir(char *path,char *dest){
    if(mkdir(dest,0777)==-1){
        cout<<"Error :"<<strerror(errno);
        return ;
    }
   // cout<<"Directory created\n";
    DIR *d;
    struct dirent *dir;
    d=opendir(path);
    if(d){
        while(((dir=readdir(d))!=NULL)){
            if((string(dir->d_name)=="..")or(string(dir->d_name)=="."));
            else{
                string f_path=string(path)+"/"+string(dir->d_name);
                char* s=new char[f_path.length()+1];
                strcpy(s,f_path.c_str());
                string d_path=string(dest)+"/"+string(dir->d_name);
                char* s1=new char[d_path.length()+1];
                strcpy(s1,d_path.c_str());
                struct stat sb;
                if(stat(s,&sb)==-1) perror("lstat");
                else{
                    if(S_ISDIR(sb.st_mode)) copy_dir(s,s1);
                    else copy_file(s,s1);
                }

            }
        }
    }
    else{
        Error("No such directory");
    }
}
void copy_file(char* path,char* dest){
    char x[1024];
    int i,o,r;
    i=open(path,O_RDONLY);
    o=open(dest,O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((r=read(i,x,sizeof(x)))>0)
        write(o,x,r);
    struct stat s,d;
    if(stat(path,&s)!=-1);
    if(stat(dest,&d)!=-1);
    int s1=chown(dest,s.st_uid,s.st_gid);
    if(s1!=0) Error("Error in ownership");
    int s2=chmod(dest,s.st_mode);
    if(s2!=0) Error("Error in permission");
}
void copy_cmd(vector<string> args){
    int l=args.size();
  //  cout<<l;
    if(l<3) Error("Invalid number of arguments");
 //   cout<<"VALID";
    else{
        for(int i=1;i<l-1;i++){
            string f_name=file_name(args[i]);
            string des=args[l-1];
            des=des+"/"+f_name;
            char *dest=new char[des.length()+1];
            strcpy(dest,des.c_str());
            char *path=new char[args[i].length()+1];
            strcpy(path,args[i].c_str());
            if(isDir(path)) copy_dir(path,dest);
            else copy_file(path,dest);
        }
    }
}

void move_cmd(vector<string> args){
    int l=args.size();
  //  cout<<l;
    if(l<3) Error("Invalid number of arguments");
 //   cout<<"VALID";
    else{
        for(int i=1;i<l-1;i++){
            string f_name=file_name(args[i]);
            string des=args[l-1];
            des=des+"/"+f_name;
            char *dest=new char[des.length()+1];
            strcpy(dest,des.c_str());
            char *path=new char[args[i].length()+1];
            strcpy(path,args[i].c_str());
            if(isDir(path)){
                copy_dir(path,dest);
                del_dir(path);
            }
            else{
                copy_file(path,dest);
                del_file(path);
            }
        }
    }
}

void rename_cmd(vector<string> args){
    string i=args[1],f=args[2];
    rename(i.c_str(),f.c_str());
}


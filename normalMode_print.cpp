#include "header.h"

using namespace std;

char *c_path;
int x=1,y=1;
stack<string> fwd_stack,back_stack;
void normalMode(){
  c_path=root;
  struct termios old_tio,new_tio;
  tcgetattr(STDIN_FILENO, &old_tio);
  new_tio=old_tio;
  new_tio.c_lflag &= (~ICANON);
  new_tio.c_lflag &= (~ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_tio);
  //CLEAR;
  cursor(1,1);
  char c;
  while(1){
    c=cin.get();
    if(c==ESC){
      c=cin.get();
      c=cin.get();
      if(c=='A'){
        if(x+win>1){
          x--;
          if(x>0) cursor(x,y);
          else if(x<=0 and x+win>=1){
            CLEAR;
            if(win>0) win--;
            cursor(1,1);
            for(int i=win;i<r_sz+win;i++){
              char *temp=new char[d_list[i].length()+1];
              strcpy(temp,d_list[i].c_str());
              print(temp,c_path);
            }
            x++;
            cursor(x,y);
          }
        }
      }        
      else if(c=='B'){
        int len;
        if(x+win<tot){
          x++;
          if(x<=r_sz) cursor(x,y);
          else if(x>r_sz and x+win<=tot){
            CLEAR;
            len=file_count()-1;
            if(tot>r_sz) win++;
            cursor(1,1);
            for(int i=win;i<=len+win;i++){
              char *temp=new char[d_list[i].length()+1];
              strcpy(temp,d_list[i].c_str());
              print(temp,c_path);
            }
            x--;
            //cursor(r_sz+1,1);
            //cout<<win;
          }
          cursor(x,y);
        }
      }
      else if(c=='C'){
        if(!fwd_stack.empty()){
          string cpath=string(c_path);
          if(flag!=1) back_stack.push(string(c_path));
          string top=fwd_stack.top();
          fwd_stack.pop();
          strcpy(c_path,top.c_str());
          flag=0;
          openDir(c_path);
          x=1;y=1;
          cursor(x,y);
        }
      }
      else if(c=='D'){
        if(!back_stack.empty()){
          string cpath=string (c_path);
          if(flag!=1) fwd_stack.push(string(c_path));
          string top=back_stack.top();
          back_stack.pop();
          strcpy(c_path,top.c_str());
          flag=0;
          openDir(c_path);
          x=1;y=1;
          cursor(x,y);
        }
      }
    }
    else if(c=='k'){
      struct winsize w;
      ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
      int r=w.ws_row,X=x;
      for(int i=1;i<r+X-1;i++){
        if(x+win>1){
          x--;
          if(x>0) cursor(x,y);
          else if(x<=0 and x+win>=1){
            CLEAR;
            if(win>0) win--;
            cursor(1,1);
            for(int i=win;i<r_sz+win;i++){
              char *temp=new char[d_list[i].length()+1];
              strcpy(temp,d_list[i].c_str());
              print(temp,c_path);
            }
            x++;
            cursor(x,y);
          }
        }
      }
    }
    else if(c=='l'){
      struct winsize w;
      ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
      int r=w.ws_row,X=x;
      for(int i=1;i<2*r-X-1;i++){
        int len;
        if(x+win<tot){
          x++;
          if(x<=r_sz) cursor(x,y);
          else if(x>r_sz and x+win<=tot){
            CLEAR;
            len=file_count()-1;
            if(tot>r_sz) win++;
            cursor(1,1);
            for(int i=win;i<=len+win;i++){
              char *temp=new char[d_list[i].length()+1];
              strcpy(temp,d_list[i].c_str());
              print(temp,c_path);
            }
            x--;
            //cursor(r_sz+1,1);
            //cout<<win;
          }
          cursor(x,y);
        }
      }
    }
    
    else if(c=='h'){
      string cpath=string(c_path);
      if(cpath!=string(root)){
        if(flag!=1) back_stack.push(string(c_path));
        clear_stack(fwd_stack);
        strcpy(c_path,root);
        flag=0;
        openDir(c_path);
        x=1;y=1;
        cursor(x,y);
      }
    }
    else if(c==127){
      string cpath=string(c_path);
      if((strcmp(c_path,root)!=0) and flag!=1){
        back_stack.push(c_path);
        clear_stack(fwd_stack);
        set_back_path(c_path);
        openDir(c_path);
        x=1;y=1;
        cursor(x,y);
      }
    }
    else if(c==10){
      string cdir=d_list[x+win-1];
      string comp_path;
      if(flag==1) comp_path=cdir;
      else comp_path=string(c_path)+"/"+cdir;
      char *path=new char[comp_path.length()+1];
      strcpy(path,comp_path.c_str());

      struct stat filestat;
      stat(path,&filestat);
      if((filestat.st_mode & S_IFMT)==S_IFDIR){
        flag=0;
        if(cdir==string("."));
        else if(cdir==string("..")){
          back_stack.push(string(c_path));
          clear_stack(fwd_stack);
          set_back_path(c_path);
        }
        else{
          if(c_path){
            back_stack.push(string(c_path));
            clear_stack(fwd_stack);
          }
          c_path=path;
        }
        openDir(c_path);
      }
      else if ((filestat.st_mode & S_IFMT) == S_IFREG){
					int fileOpen=open("/dev/null",O_WRONLY);
					dup2(fileOpen,2);
					close(fileOpen);
					pid_t pID = fork();
					if(pID == 0)
					{
						execlp("xdg-open","xdg-open",path,NULL);
						exit(0);
					} 
      }
    }
    else if(c==':'){
      cursor(r_sz+1,1);
      printf("\033[2K");
      cout<<"$";
      int res=commandMode();
      CURSOR;
      if(res==1) {
        openDir(c_path);
        while(res==1){
            cursor(r_sz+1,1);
            printf("\033[2K");
            cout<<"$";
            res=commandMode();
            CURSOR;
        }
      }
      else{
        flag=0;
        openDir(c_path);
      }
    }
    else if(c=='q'){
      cursor(r_sz+1,1);
      break;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}


void print(const char *d_name,const char *root){
  string f_path;
  if(flag==1) f_path=string(d_name);
  else f_path=string(root)+"/"+string(d_name);
  char *path=new char[f_path.length()+1];
  strcpy(path,f_path.c_str());
  struct passwd *pw;
  struct group *gp;
  char *c;
  struct stat fileStat;
  stat(path,&fileStat); 
  //cout<<"FILE NAME\t\t\tSIZE  USER OW   GROUP OW  PERMISSIONS  LAST MODIFIED\n";
    stat(d_name,&fileStat);
    cout<<setw(30)<<left<<d_name;
    cout<<setw(6)<<right<<fileStat.st_size;
    pw=getpwuid(fileStat.st_uid);
    cout<<setw(8)<<right<<pw->pw_name;
    gp=getgrgid(fileStat.st_gid);
    cout<<setw(10)<<right<<gp->gr_name;
    
    printf( (S_ISDIR(fileStat.st_mode)) ? "    d" : "    -");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
    printf("   ");
    c=ctime(&fileStat.st_mtime);
    for(int i=4;i<=15;i++)
      printf("%c",c[i]);
    printf("\n");
}




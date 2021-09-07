#include "header.h"
vector<string> args;

string absPath(string s){
    char c1=s[0];
    string abs_path="",base_path=string(root);
 //   cout<<"Root is: "<<root<<endl;
    if(c1=='/') abs_path=base_path+s;
    else if(c1=='~') abs_path=base_path+s.substr(1,s.length());            
    else if(c1=='.') abs_path=string(c_path)+s.substr(1,s.length());
    else abs_path=string(c_path)+"/"+s;
    return abs_path;
}
void input_path(string s){
    int z=0;
    args.clear();
    for(int i=0;i<s.length();i++){
        string s1="";
        while(s[i]!=' ' and i<s.length()){
            if(s[i]=='\\') s1+=s[i+1],i+=2;
            else s1+=s[i++];
        }
        if(z){
            string abs_path=absPath(s1);
            args.push_back(abs_path);
        }
        else{
            args.push_back(s1);
            if(args[0]!="create_file" and args[0]!="create_dir" and args[0]!="search") z=1;
        }
    }
}

void next_cmd(){
    cursor(r_sz+1,1);
   // printf("\033[2K");
    printf("$");
}

int commandMode(){
    char c;
    do{
        string inp;
        while((c=getchar())!=10 and c!=ESC){
            if(c==127){
                //next_cmd;
                cursor(r_sz+1,1);
                printf("\033[2K");
                printf("$");
                if(inp.length()<=1) inp="";
                else inp=inp.substr(0,inp.length()-1);
                cout<<inp;
            }
            else{
                inp=inp+c;
                cout<<c;
            }
        }
        input_path(inp);
        if(c==10){
            string ar=args[0];
            if(ar=="copy") copy_cmd(args);
            else if(ar=="move") move_cmd(args);//cout<<"MOVE"<<endl;
            else if(ar=="rename") rename_cmd(args);//cout<<"Rename"<<endl;
            else if(ar=="create_file") create_file(args);//cout<<"CREATE File\n";
            else if(ar=="create_dir") create_dir(args);//cout<<"create dir\n";
            else if(ar=="delete_file") removeFile(args);//cout<<"delete file\n";
            else if(ar=="delete_dir") removeDir(args);//cout<<"delete_dir\n";
            else if(ar=="goto") {
                //cout<<"GOTO\n";
                string goto_p=goto_path(args);
                char *path=new char[goto_p.length()+1];
                strcpy(path,goto_p.c_str());
                back_stack.push(string(c_path));
                clear_stack(fwd_stack);
                c_path=path;
                return 1;
            }
            else if(ar=="search"){
                if(search(args)==1)cout<<"\nTRUE";
                else cout<<"\nFALSE";
                //cout<<"SEARCH\n";
            }
            else cout<<"\nInvalid command";
            cout<<endl;
            next_cmd();
        }
    }while(c!=ESC);
    return 0;
}
void Error(string s){
    cout<<endl<<"\033[0;31m"<<s<<endl;
    cout<<"\033[0m";
    cout<<"$";
}
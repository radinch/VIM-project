#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_SIZE 1000

char command[MAX_SIZE];
char clipboard[MAX_SIZE];

//Main commands
void createfile(char address[]);
void cat(char address[]);
void insertstr(char address[],char string[],int line_no,int start_pos);
void removestr();
void copystr();
void cutstr();
void pastestr();
void find();
void grep();
void undo();
void text_comparator();
void tree(int depth,int depth_buff,char *directory,int a);
void auto_indent(char address[]);

//Auxiliary functions
void clear(char ch[]);
void make_dir(char address[]);
void delete_quote_v1(char address[]);
void input_file_address(char address[]);
void input_string(char string[]);
int check_correctness(char * p,int length,char temp[]);//for checking weather the absolute word is found or not
void check_find_options(int *options,int *n);
int convert_stiring(char string[]);
int count_words(char *string,char *p);
void check_grep_options(int mark[],char string[]);
void input_file_address_v2(char address[]);
void file_name(char address[],char buffer[]);
void open_block(char *correct_form);

int main(){
    char buff[MAX_SIZE],address[MAX_SIZE],string[MAX_SIZE];
    int flag=1;
    while(flag){
        scanf("%s",command);
        if(!strcmp(command,"exit")){
            printf("Good Luck!");
            flag=0;
        }
        else if(!strcmp(command,"createfile")){
            clear(address);
            clear(buff);
            scanf("%s",buff);
            if(strcmp(buff,"--file")){
                char ch[50];
                scanf("%[^\n]%*c",ch);
                printf("Invalid command\n");
                continue;
            }
            input_file_address(address);
            createfile(address);
        }
        else if(!strcmp(command,"cat")){
            clear(address);
            clear(buff);
            scanf("%s",buff);
            if(strcmp(buff,"--file")){
                char ch[50];
                scanf("%[^\n]%*c",ch);
                printf("Invalid command\n");
                continue;
            }
            input_file_address(address);
            cat(address);
        }
        else if(!strcmp(command,"insertstr")){
            clear(buff);
            clear(address);
            clear(string);
            int line_no,start_pos; //for position of string
            scanf("%s",buff);
            if(strcmp(buff,"--file")){
                char ch[50];
                scanf("%[^\n]%*c",ch);
                printf("Invalid command\n");
                continue;
            }
            input_file_address(address);
            clear(buff);
            scanf("%s",buff);
            if(strcmp(buff,"--str")){
                char ch[50];
                scanf("%[^\n]%*c",ch);
                printf("Invalid command\n");
                continue;
            }
            input_string(string);
            clear(buff);
            scanf("%s",buff);
            if(strcmp(buff,"--pos")){
                char ch[50];
                scanf("%[^\n]%*c",ch);
                printf("Invalid command\n");
                continue;
            }
            char ch;
            scanf("%d%c%d",&line_no,&ch,&start_pos);
            insertstr(address,string,line_no,start_pos);
        }
        else if(!strcmp(command,"removestr")){
            removestr();
        }
        else if(!strcmp(command,"copystr")){
            copystr();
        }
        else if(!strcmp(command,"cutstr")){
            cutstr();
        }
        else if(!strcmp(command,"pastestr")){
            pastestr();
        }
        else if(!strcmp(command,"find")){
            find();
        }
        else if(!strcmp(command,"grep")){
            grep();
        }
        else if(!strcmp(command,"undo")){
            undo();
        }
        else if(!strcmp(command,"compare")){
            text_comparator();
        }
        else if(!strcmp(command,"tree")){
            int depth;
            char *directory=(char *)malloc(MAX_SIZE*sizeof(char));
            char *dir_buff=(char *)malloc(MAX_SIZE*sizeof(char));
            strcpy(directory,"./root");
            scanf("%d",&depth);
            if(depth<=-1){
                printf("Invalid depth\n");
                continue;
            }
            tree(depth,depth,directory,1);
        }
        else if(!strcmp(command,"auto-indent")){
            clear(address);
            input_file_address(address);
            auto_indent(address);
        }
        else{
            char junk[MAX_SIZE]; //to avoid repeating print invalid command
            scanf("%[^\n]%*c",junk);
            printf("Invalid command\n");
        }
        clear(command);
    }
    return 0;
}

void clear(char ch[]){
    //int length=strlen(ch);
    for(int i=0;i<MAX_SIZE;i++){
        ch[i]=0;
    }
}

void make_dir(char address[]){
    char buff[MAX_SIZE]={0};  //for making new directories
    //clear(buff);
    int i=0;
    while(address[i]!=0){
        if(address[i]=='/'){
            mkdir(buff);
        }
        buff[i]=address[i];
        i++;
    }
}

void delete_quote_v1(char address[]){
    char buffer[MAX_SIZE];
    for(int i=0;i<MAX_SIZE;i++){
        buffer[i]=address[i];
    }
    clear(address);
    int count=0;
    for(int i=0;i<MAX_SIZE ;i++){
        if(buffer[i]!='"' && i!=0){
            address[count]=buffer[i];
            count++;
        }
    }
}

void file_name(char address[],char buffer[]){
    clear(buffer);
    buffer[0]='u';
    buffer[1]='/';
    int count=strlen(address)-1;
    while(address[count-1]!='/'){
        count--;
    }
    for(int i=count;i<strlen(address);i++){
        buffer[i-count+2]=address[i];
    }
}

void file_name_2(char address[],char buffer[]){
    clear(buffer);
    buffer[0]='u';
    buffer[1]='/';
    buffer[2]='.';
    int count=strlen(address)-1;
    while(address[count-1]!='/'){
        count--;
    }
    for(int i=count;i<strlen(address);i++){
        buffer[i-count+3]=address[i];
    }
}

void file_name_3(char address[],char buffer[]){
    clear(buffer);
    int count=strlen(address)-1;
    while(address[count-1]!='/'){
        count--;
    }
    for(int i=count;i<strlen(address);i++){
        buffer[i-count]=address[i];
    }
}

void input_file_address(char address[]){
    char buffer[MAX_SIZE]={0};
    char temp[MAX_SIZE]={0};
    char ch=getchar();
    ch=getchar();
    if(ch=='"'){
        ch=0;
        int count=0;
        while(ch!='"'){
            ch=getchar();
            address[count]=ch;
            count++;
        }
    }
    else{
        scanf("%s",address);
    }
    int length=strlen(address);
    if(ch=='"' && address[length-1]=='"'){
        delete_quote_v1(address);
    }
    file_name(address,buffer);
    FILE *und=fopen(buffer,"w");
    FILE * file=fopen(address,"r");
    while(fgets(temp,MAX_SIZE,file)!=NULL){
        fputs(temp,und);
    }
    fclose(und);
    fclose(file);
}

void input_file_address_v2(char address[]){
    char buffer[MAX_SIZE]={0};
    char temp[MAX_SIZE]={0};
    char ch=getchar();
    if(ch=='"'){
        ch=0;
        int count=0;
        while(ch!='"'){
            ch=getchar();
            address[count]=ch;
            count++;
        }
    }
    else{
        scanf("%s",address);
    }
    int length=strlen(address);
    if(ch=='"' && address[length-1]=='"'){
        delete_quote_v1(address);
    }
    file_name(address,buffer);
    FILE *und=fopen(buffer,"w");
    FILE * file=fopen(address,"r");
    while(fgets(temp,MAX_SIZE,file)!=NULL){
        fputs(temp,und);
    }
    fclose(und);
    fclose(file);
}

void input_string(char string[]){
    char ch;
    ch=getchar();
    ch=getchar();
    int count=0;
    if(ch!='"'){
        while(ch!=32){
            string[count]=ch;
            ch=getchar();
            count++;
        }
    }
    else{
        ch=0;
        int flag=1;
        while(flag){
            ch=getchar();
            if(ch!='"'){
                string[count]=ch;
                count++;
            }
            else if(ch=='"' && string[count-1]=='\\'){
                string[count]=ch;
                count++;
            }
            else{
                flag=0;
            }

        }
    }
}

int check_correctness(char *p,int length,char temp[]){
    if(*(p+length)>=32 && *(p+length)<=47 || *(p+length)=='?' ||*(p+length)==EOF || *(p+length)=='\n'){
        if(*(p-1)>=32 && *(p-1)<=47 || *(p-1)=='?' || p-temp==0){
            return 1;
        }
    }
    return 0;
}

void check_find_options(int *options,int *n){
    char flag[MAX_SIZE]={0};
    char ch;
    ch=getchar();
    while(ch!='\n'){
        scanf("%s",flag);
        if(!strcmp(flag,"-count")){
            *options=1;
        }
        else if(!strcmp(flag,"-at")){
            *(options+1)=1;
            scanf("%d",n);
        }
        else if(!strcmp(flag,"-byword")){
            *(options+2)=1;
        }
        else if(!strcmp(flag,"-all")){
            *(options+3)=1;
        }
        else{
            char ch[50];
            scanf("%[^\n]%*c",ch);
            printf("Invalid command\n");
            return;
        }
        clear(flag);
        ch=getchar();
    }
}

void check_grep_options(int mark[],char string[]){
    char flag[MAX_SIZE]={0};
    char ch;
    ch=getchar();
    while(ch!='\n'){
        scanf("%s",flag);
        if(!strcmp(flag,"--str")){
            input_string(string);
        }
        else if(!strcmp(flag,"--files")){
            return;
        }
        else if(!strcmp(flag,"-c")){
            mark[0]=1;
        }
        else if(!strcmp(flag,"-l")){
            mark[1]=1;
        }
        else{
            char ch[50];
            scanf("%[^\n]%*c",ch);
            printf("Invalid command\n");
            return;
        }
        clear(flag);
        ch=getchar();
    }
}

int convert_stiring(char string[]){
    char buff[MAX_SIZE]={0};
    int count=0;
    int flag=0;
    for(int i=0;i<strlen(string);i++){
        if(string[i]!='\\' && string[i]!='n' && string[i]!='"'){
            buff[count]=string[i];
            count++;
        }
        else if(string[i]=='n'){
            if(i>=2 && string[i-1]=='\\' && string[i-2]=='\\'){
                buff[count]='n';
                count++;
            }
            else if(i==0 || string[i-1]!='\\'){
                buff[count]='n';
                count++;
            }
            else{
                buff[count]='\n';
                count++;
            }
        }
        else if(string[i]=='"' && string[i-1]=='\\'){
            buff[count]='"';
            count++;
        }
        else if(string[i]=='\\' && i!=0 && string[i-1]=='\\'){
            buff[count]='\\';
            count++;
        }
        else if(string[i]=='*' && string[i-1]=='\\'){
            buff[count]='*';
            count++;
        }
        else if(string[i]=='*'){
            buff[count]='*';
            count++;
            flag=1;
        }
    }
    clear(string);
    strcpy(string,buff);
    return flag;
}

int count_words(char *string,char *p){
    int count=0;
    for(int i=0;string+i<p;i++){
        if(i!=0 && string[i]==' ' && string[i+1]!=' ' && string[i+1]!='\n'){
            count++;
        }
    }
    return count+1;
}

void open_block(char *ptr){
    char *buff=(char *)malloc(sizeof(char)*MAX_SIZE);
    clear(buff);
    if(*(ptr-1)!=' '){
        for(int i=strlen(ptr);i>0;i--){
            *(ptr+i)=*(ptr+i-1);
        }
        *ptr=' ';
        return;
    }
    int length=strlen(ptr);
    while(*(ptr-2)==' '){
        for(int i=-1;i<length;i++){
            *(ptr+i)=*(ptr+i+1);
        }
        ptr--;
    }

}

void createfile(char address[]){
    make_dir(address);
    FILE * f;
    if(access(address,F_OK)==0){
        printf("Error: This file already exists\n");
    }
    else{
        printf("Success\n");
        FILE * f1=fopen(address,"w");
        fclose(f1);
    }
}

void cat(char address[]){
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
    }
    else{
        FILE * f=fopen(address,"r");
        char c="a";
        while(c!=EOF){
            c=getc(f);
            if(c!=EOF)
            printf("%c",c);
        }
        printf("\n");
    }
}

void insertstr(char address[],char string[],int line_no,int start_pos){
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE * file =fopen(address,"r");
    FILE * file_buff=fopen("file_buff.txt","w");
    int l=1,p=0;
    char c;
    while(l!=line_no){
        c=getc(file);
        putc(c,file_buff);
        if(c=='\n')
            l++;
    }
    for(int i=0;i<start_pos;i++){
        c=getc(file);
        putc(c,file_buff);
    }
    convert_stiring(string);
    fputs(string,file_buff);
    while(c!=EOF){
        c=getc(file);
        putc(c,file_buff);
    }
    fclose(file);
    fclose(file_buff);
    file=fopen(address,"w");
    file_buff=fopen("file_buff.txt","r");
    c=0;
    while(c!=EOF){
        c=getc(file_buff);
        if(c!=EOF)
        fputc(c,file);
    }
    fclose(file);
    fclose(file_buff);
    printf("Success\n");
}

void removestr(){
    int line_no,start_pos; //for position of string that we want to remove
    int r_num; //number of characters that we want to remove
    int countChar=0; //for counting characters
    int buffer=0;
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0};
    scanf("%s",buff);
    if(strcmp(buff,"--file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"--pos")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch;
    scanf("%d%c%d",&line_no,&ch,&start_pos);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-size")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    scanf("%d",&r_num);
    buffer=r_num;
    clear(buff);
    scanf("%s",buff);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE * file =fopen(address,"r");
    FILE * file_buff=fopen("file_buff.txt","w");
    int l=1,p=0;
    char c;
    while(l!=line_no){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
        if(c=='\n')
            l++;
    }
    for(int i=0;i<start_pos;i++){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
    }
    while(c!=EOF){
        c=getc(file);
        if(r_num<=0 || !strcmp(buff,"-b"))
            putc(c,file_buff);
        r_num--;
    }
    fclose(file);
    fclose(file_buff);
    file=fopen(address,"w");
    file_buff=fopen("file_buff.txt","r");
    c=0;
    int char_num=0;
    while(c!=EOF){
        c=getc(file_buff);
        char_num++;
        if(c!=EOF){
            if(char_num<countChar-buffer+1 || char_num>countChar || !strcmp(buff,"-f"))
                fputc(c,file);
        }
    }
    fclose(file);
    fclose(file_buff);
    printf("Success\n");
}

void copystr(){
    clear(clipboard);
    int line_no,start_pos; //for position of string that we want to copy
    int r_num; //number of characters that we want to copy
    int countChar=0; //for counting characters
    int buffer=0;
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0};
    scanf("%s",buff);
    if(strcmp(buff,"--file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"--pos")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch;
    scanf("%d%c%d",&line_no,&ch,&start_pos);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-size")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    scanf("%d",&r_num);
    buffer=r_num;
    clear(buff);
    scanf("%s",buff);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE * file =fopen(address,"r");
    FILE * file_buff=fopen("file_buff.txt","w");
    int l=1,p=0;
    char c;
    while(l!=line_no){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
        if(c=='\n')
            l++;
    }
    for(int i=0;i<start_pos;i++){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
    }
    int copy_num=0;
    while(c!=EOF){
        c=getc(file);
        if(r_num>0 && !strcmp(buff,"-f")){
            clipboard[copy_num]=c;
            copy_num++;
        }
        putc(c,file_buff);
        r_num--;
    }
    fclose(file);
    fclose(file_buff);
    file=fopen(address,"w");
    file_buff=fopen("file_buff.txt","r");
    c=0;
    int char_num=0;
    while(c!=EOF){
        c=getc(file_buff);
        char_num++;
        if(c!=EOF){
            fputc(c,file);
            if(char_num>=countChar-buffer+1 && char_num<=countChar && !strcmp(buff,"-b")){
                clipboard[copy_num]=c;
                copy_num++;
            }
        }
    }
    fclose(file);
    fclose(file_buff);
    printf("Success\n");
}

void cutstr(){
    clear(clipboard);
    int line_no,start_pos; //for position of string that we want to remove and copy
    int r_num; //number of characters that we want to remove and copy
    int countChar=0; //for counting characters
    int buffer=0;
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0};
    scanf("%s",buff);
    if(strcmp(buff,"--file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"--pos")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch;
    scanf("%d%c%d",&line_no,&ch,&start_pos);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-size")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    scanf("%d",&r_num);
    buffer=r_num;
    clear(buff);
    scanf("%s",buff);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE * file =fopen(address,"r");
    FILE * file_buff=fopen("file_buff.txt","w");
    int l=1,p=0;
    char c;
    while(l!=line_no){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
        if(c=='\n')
            l++;
    }
    for(int i=0;i<start_pos;i++){
        c=getc(file);
        countChar++;
        putc(c,file_buff);
    }
    int copy_num=0;
    while(c!=EOF){
        c=getc(file);
        if(r_num<=0 || !strcmp(buff,"-b"))
            putc(c,file_buff);
        if(r_num>0 && !strcmp(buff,"-f")){
            clipboard[copy_num]=c;
            copy_num++;
        }
        r_num--;
    }
    fclose(file);
    fclose(file_buff);
    file=fopen(address,"w");
    file_buff=fopen("file_buff.txt","r");
    c=0;
    int char_num=0;
    while(c!=EOF){
        c=getc(file_buff);
        char_num++;
        if(c!=EOF){
            if(char_num<countChar-buffer+1 || char_num>countChar || !strcmp(buff,"-f"))
                fputc(c,file);
            if(char_num>=countChar-buffer+1 && char_num<=countChar && !strcmp(buff,"-b")){
                clipboard[copy_num]=c;
                copy_num++;
            }

        }
    }
    fclose(file);
    fclose(file_buff);
    printf("Success\n");
}

void pastestr(){
    int line_no,start_pos; //for position of string
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0},string[MAX_SIZE]={0};
    scanf("%s",buff);
    if(strcmp(buff,"--file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"--pos")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch;
    scanf("%d%c%d",&line_no,&ch,&start_pos);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE * file =fopen(address,"r");
    FILE * file_buff=fopen("file_buff.txt","w");
    int l=1,p=0;
    char c;
    while(l!=line_no){
        c=getc(file);
        putc(c,file_buff);
        if(c=='\n')
            l++;
    }
    for(int i=0;i<start_pos;i++){
        c=getc(file);
        putc(c,file_buff);
    }
    fputs(clipboard,file_buff);
    while(c!=EOF){
        c=getc(file);
        putc(c,file_buff);
    }
    fclose(file);
    fclose(file_buff);
    file=fopen(address,"w");
    file_buff=fopen("file_buff.txt","r");
    c=0;
    while(c!=EOF){
        c=getc(file_buff);
        if(c!=EOF)
        fputc(c,file);
    }
    fclose(file);
    fclose(file_buff);
    printf("Success\n");
}

void find(){
    int line_no,start_pos; //for position of string
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0},string[MAX_SIZE]={0},temp[MAX_SIZE]={0};
    int flag=0; //for checking the existence of the string
    int n=1;
    int *options=(int *)malloc(sizeof(int)*4),*ptr=&n; //just for checking this useless options
    for(int i=0;i<4;i++){
        *(options+i)=0;
    }
    scanf("%s",buff);
    if(strcmp(buff,"--str")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_string(string);
    convert_stiring(string);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"--file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    check_find_options(options,ptr);
    FILE * file =fopen(address,"r");
    if(*options){
        if(*(options+1)==0 && *(options+2)==0 && *(options+3)==0){
            char *p;
            int count=0;
            while(fgets(temp,MAX_SIZE,file)!=NULL){
                for(int i=0;i<strlen(temp);i++){
                    if(strstr(temp+i,string)!=NULL){
                        char *p=strstr(temp+i,string);
                        int length=strlen(string);
                        if(check_correctness(p,length,temp)){
                            if(temp+i==p)
                                count++;
                        }
                    }
                }
                clear(temp);
            }
            printf("This phrase was found %d times\n",count);
        }
        else{
            printf("You cannot use these options simultaneously\n");
        }
    }
    else if(*(options+3) && *(options+1)){
        printf("You cannot use these options simultaneously\n");
    }
    else if(*(options+3)){
        char *p;
        int countChar=0;
        int countWord=0;
        int count=0;
        while(fgets(temp,MAX_SIZE,file)!=NULL){
            p=temp+strlen(temp)-1;
            for(int i=0;i<strlen(temp);i++){
                if(strstr(temp+i,string)!=NULL){
                    p=strstr(temp+i,string);
                    int length=strlen(string);
                    if(check_correctness(p,length,temp)){
                        if(temp+i==p){
                            flag=1;
                            if(*(options+2)){
                                printf("%d ",countWord+count_words(temp,p));
                            }
                            else{
                                printf("%d ",countChar+p-temp);
                            }
                        }
                    }
                }
            }
            countChar+=strlen(temp);
            p=temp+strlen(temp)-1;
            countWord+=count_words(temp,p);
            clear(temp);
        }
        if(flag==0){
            printf("%d\n",-1);
        }
        else{
            printf("\n");
        }
    }
    else{
        char *p;
        int countChar=0;
        int countWord=0;
        int count=0;
        while(fgets(temp,MAX_SIZE,file)!=NULL){
            p=temp+strlen(temp)-1;
            for(int i=0;i<strlen(temp);i++){
                if(strstr(temp+i,string)!=NULL){
                    p=strstr(temp+i,string);
                    int length=strlen(string);
                    if(check_correctness(p,length,temp)){
                        if(temp+i==p){
                            count++;
                        }
                        if(count==n){
                            countChar+=p-temp;
                            countWord+=count_words(temp,p);
                            flag=1;
                            break;
                        }
                    }
                }
            }
            if(flag==1){
                break;
            }
            countChar+=strlen(temp);
            p=temp+strlen(temp)-1;
            countWord+=count_words(temp,p);
            clear(temp);
        }
        if(flag==0){
            printf("%d\n",-1);
        }
        else if(*(options+2)){
            printf("%d\n",countWord);
        }
        else{
            printf("Found: index of the first Character is [%d]\n",countChar);
        }
    }
    fclose(file);
}

void grep(){
    char buff1[MAX_SIZE][MAX_SIZE]={0},buff2[MAX_SIZE][MAX_SIZE]={0},address[MAX_SIZE]={0},string[MAX_SIZE]={0},temp[MAX_SIZE]={0};
    int mark[2]={0,0};
    check_grep_options(mark,string);
    convert_stiring(string);
    char ch=0;
    ch=getchar();
    int count_lines=0;
    FILE *file;
    int flag1=0;
    int flag2=0;
    int count1=0;
    int count2=0;
    while(ch!='\n'){
        input_file_address_v2(address);
        if(access(address,F_OK)!=0){
            printf("Error: /%s does not exist\nplease input the file again\n",address);
            return;
        }
        file=fopen(address,"r");
        while(fgets(temp,MAX_SIZE,file)!=NULL){
            if(strstr(temp,string)!=NULL){
                count_lines++;
                if(mark[1]==1){
                    for(int i=0;i<strlen(address);i++){
                        buff1[count1][i]=address[i];
                    }
                    count1++;
                    flag1=1;
                    break;
                }
                if(mark[0]==0 && mark[1]==0){
                    flag2=1;
                    for(int i=0;i<strlen(temp);i++){
                        if(temp[i]!='\n'){
                            buff2[count2][i]=temp[i];
                        }
                    }
                    count2++;
                }
            }
        }
        clear(address);
        ch=getchar();
    }
    fclose(file);
    if(mark[0]==1){
        printf("%d\n",count_lines);
    }
    else if(flag1==1){
        for(int i=0;i<count1;i++){
            printf("%s\n",buff1[i]);
        }
    }
    else if(flag2==1){
        for(int i=0;i<count2;i++){
            printf("%s\n",buff2[i]);
        }
    }
    else if(flag1==0 && flag2==0){
        printf("This pattern does not exist in any file\n");
    }

}

void undo(){
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0},string[MAX_SIZE]={0},temp[MAX_SIZE]={0};
    char buffer[MAX_SIZE]={0};
    scanf("%s",buff);
    char ch=getchar();
    ch=getchar();
    if(ch=='"'){
        ch=0;
        int count=0;
        while(ch!='"'){
            ch=getchar();
            address[count]=ch;
            count++;
        }
    }
    else{
        scanf("%s",address);
    }
    int length=strlen(address);
    if(ch=='"' && address[length-1]=='"'){
        delete_quote_v1(address);
    }
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    file_name(address,buffer);
    int n=strlen(buffer);
    file_name_2(address,buffer);
    FILE *file=fopen(address,"r"),*und=fopen(buffer,"w");
    while(fgets(temp,MAX_SIZE,file)!=NULL){
        fputs(temp,und);
    }
    fclose(file);
    fclose(und);
    file_name(address,buffer);
    file=fopen(address,"w");
    und=fopen(buffer,"r");
    while(fgets(temp,MAX_SIZE,und)!=NULL){
        fputs(temp,file);
    }
    fclose(file);
    fclose(und);
    file_name_2(address,buffer);
    file=fopen(buffer,"r");
    file_name(address,buffer);
    und=fopen(buffer,"w");
    while(fgets(temp,MAX_SIZE,file)!=NULL){
        fputs(temp,und);
    }
    fclose(file);
    fclose(und);
    printf("Success\n");
}

void text_comparator(){
    int count=0;
    int line_number=0;
    int flag1=1,flag2=1;
    char address1[MAX_SIZE]={0},address2[MAX_SIZE]={0};
    char temp1[MAX_SIZE]={0},temp2[MAX_SIZE]={0};
    char buff[MAX_SIZE][MAX_SIZE]={0};
    input_file_address(address1);
    input_file_address(address2);
    if(access(address1,F_OK)!=0){
        printf("Error: /%s does not exist\nplease input the file again\n",address1);
        return;
    }
    if(access(address2,F_OK)!=0){
        printf("Error: /%s does not exist\nplease input the file again\n",address2);
        return;
    }
    FILE *file1=fopen(address1,"r"),*file2=fopen(address2,"r");
    while(flag1 && flag2){
        if(fgets(temp1,MAX_SIZE,file1)==NULL){
            flag1=0;
        }
        if(fgets(temp2,MAX_SIZE,file2)==NULL){
            flag2=0;
        }
        line_number++;
        if(flag1==0 || flag2==0){
            break;
        }
        if(strcmp(temp1,temp2)){
            printf("============ #%d ============\n",line_number);
            for(int i=0;i<strlen(temp1);i++){
                if(temp1[i]!='\n'){
                    printf("%c",temp1[i]);
                }
            }
            printf("\n");
            for(int i=0;i<strlen(temp2);i++){
                if(temp2[i]!='\n'){
                    printf("%c",temp2[i]);
                }
            }
            printf("\n");
        }
    }
    if(flag1==0 && flag2==0){
        return;
    }
    else if(flag1==0){
        int end_line=line_number;
        do{
            for(int i=0;i<strlen(temp2);i++){
                if(temp2[i]!='\n'){
                    buff[count][i]=temp2[i];
                }
            }
            count++;
            end_line++;
        }while(fgets(temp2,MAX_SIZE,file2)!=NULL);
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",line_number,end_line-1);
        for(int i=0;i<count;i++){
            printf("%s\n",buff[i]);
        }
    }
    else{
        int end_line=line_number;
        do{
            for(int i=0;i<strlen(temp1);i++){
                if(temp1[i]!='\n'){
                    buff[count][i]=temp1[i];
                }
            }
            count++;
            end_line++;
        }while(fgets(temp1,MAX_SIZE,file1)!=NULL);
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",line_number,end_line-1);
        for(int i=0;i<count;i++){
            printf("%s\n",buff[i]);
        }
    }
}

void tree(int depth,int depth_buff,char* directory,int a){
    if(depth_buff==-2){
        return;
    }
    struct dirent *de;
    DIR *dir=opendir(directory);
    if(dir==NULL){
        char buff[MAX_SIZE];
        file_name_3(directory,buff);
        printf("|");
        for(int i=0;i<depth-depth_buff-1;i++){
            printf("  ");
        }
        if(depth-1==depth_buff)
            printf("____%s\n",buff);
        else
            printf("|____%s\n",buff);
        if(depth-1!=depth_buff || a!=0)
            printf("|");
        for(int i=0;i<depth-depth_buff-1;i++){
            printf("  ");
        }
        if(depth-1!=depth_buff && a==1)
            printf("|\n");
        else{
            printf("\n");
        }
        return;
    }

    char buff[MAX_SIZE];
    file_name_3(directory,buff);
    if(strcmp(buff,"root")){
        printf("|");
        for(int i=0;i<depth-depth_buff-1;i++){
            printf("  ");
        }
        if(depth-1==depth_buff)
            printf("____%s\n",buff);
        else
            printf("|____%s\n",buff);
        if(depth-1!=depth_buff || a!=0)
            printf("|");
        for(int i=0;i<depth-depth_buff-1;i++){
            printf("  ");
        }
        if(depth-1!=depth_buff && a==1)
            printf("|\n");
        else{
            printf("\n");
        }
    }
    char *dir_buff=(char *)malloc(sizeof(char)*MAX_SIZE);
    strcpy(dir_buff,directory);
    int flag=1;
    de=readdir(dir);
    if(de==NULL)
        flag=0;
    while(flag){
        int f=0;
        if(*(de->d_name)!='.'){
            strcat(dir_buff,"/");
            strcat(dir_buff,de->d_name);
            f=1;
        }
        if((de=readdir(dir))==NULL){
            flag=0;
        }
        if(f==1){
            tree(depth,depth_buff-1,dir_buff,flag);
        }
        strcpy(dir_buff,directory);
    }
    closedir(dir);
}

void auto_indent(char address[]){
    char *temp=(char *)malloc(sizeof(char)*MAX_SIZE);
    char *correct_form=(char *)malloc(sizeof(char)*MAX_SIZE);
    int count=0;
    clear(temp);
    if(access(address,F_OK)!=0){
        printf("Error: This file does not exist\n");
        return;
    }
    FILE *file=fopen(address,"r");
    fgets(temp,MAX_SIZE,file);
    clear(correct_form);
    int depth=0;
    int flag=0,flag1=0;
    for(int i=0;i<strlen(temp);i++){
        if(temp[i]!=' ' && temp[i]!='}' && flag1==0){
            count=strlen(correct_form);
            correct_form[count]=temp[i];
            flag=0;
        }
        if(temp[i]!=' ' && temp[i]!='}' && flag1==1){
            strcat(correct_form,"\n");
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }
            count=strlen(correct_form);
            correct_form[count]=temp[i];
            flag=0;
            flag1=0;
        }
        if(temp[i]==' ' && flag==0){
            count=strlen(correct_form);
            correct_form[count]=temp[i];
        }
        if(temp[i]=='{' && i==0){
            depth++;
            count=strlen(correct_form);
            correct_form[count]='\n';
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }
            flag=1;
        }
        else if(temp[i]=='{' && correct_form[count-1-4*depth]=='\n'){
            depth++;
            count=strlen(correct_form);
            correct_form[count]='\n';
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }
            flag=1;
        }
        else if(temp[i]=='{'){
            depth++;
            open_block(correct_form + count);
            count=strlen(correct_form);
            correct_form[count]='\n';
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }
            flag=1;
        }
        else if(temp[i]=='}'){
            flag=1;
            flag1=1;
            depth--;
            char *ptr=correct_form+strlen(correct_form)-1;
            while(*(ptr)==' '){
                *ptr=0;
                ptr--;
            }
            count=strlen(correct_form);
            if(correct_form[count-1]!='\n')
                correct_form[count]='\n';
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }
            count=strlen(correct_form);
            correct_form[count]='}';
            /*strcat(correct_form,"\n");
            for(int i=0;i<depth*4;i++){
                strcat(correct_form," ");
            }*/
        }
    }
    fclose(file);
    file=fopen(address,"w");
    fprintf(file,"%s",correct_form);
    fclose(file);
    printf("%s\n",correct_form);
}

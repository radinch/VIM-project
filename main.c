#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#define MAX_SIZE 20

char command[100];

//Main commands
void createfile();
void cat();
void insertstr();

//Auxiliary functions
void clear(char ch[]);
void make_dir(char address[]);
void delete_quote_v1(char address[]);

int main()
{
    int flag=1;
    while(flag){
        scanf("%s",command);
        if(!strcmp(command,"exit")){
            printf("Good Luck!");
            flag=0;
        }
        else if(!strcmp(command,"createfile")){
            createfile();
        }
        else if(!strcmp(command,"cat")){
            cat();
        }
        else if(!strcmp(command,"insertstr")){
            insertstr();
        }
        else{
            char junk[100]; //to avoid repeating print invalid command
            scanf("%[^\n]%*c",junk);
            printf("Invalid command\n");
        }
        clear(command);
    }
    return 0;
}

void clear(char ch[]){
    //int length=strlen(ch);
    for(int i=0;i<100;i++){
        ch[i]=0;
    }
}

void make_dir(char address[]){
    char buff[100]={0};  //for making new directories
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
    char buffer[100];
    for(int i=0;i<100;i++){
        buffer[i]=address[i];
    }
    clear(address);
    int count=0;
    for(int i=0;i<100;i++){
        if(buffer[i]!='"' && i!=0){
            address[count]=buffer[i];
            count++;
        }
    }
}

void createfile(){
    char buff[100],address[100];
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch=getchar();
    ch=getchar();
    scanf("%[^\n]%*c",address);
    int length=strlen(address);
    if(ch=='"' && address[length-1]=='"'){
        delete_quote_v1(address);
    }
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

void cat(){
    char buff[100],address[100];
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    char ch=getchar();
    ch=getchar();
    scanf("%[^\n]%*c",address);
    int length=strlen(address);
    if(ch=='"' && address[length-1]=='"'){
        delete_quote_v1(address);
    }
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

void insertstr(){
    int line_no,start_pos; //for position of string
    char buff[100]={0},address[100]={0},string[100]={0};
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
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
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-str")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
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
        while(ch!='"'){
            ch=getchar();
            if(ch!='"'){
                string[count]=ch;
                count++;
            }
            if(ch=='"' && string[count]==92){
                string[count]=ch;
                count++;
            }
        }
    }
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
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
}


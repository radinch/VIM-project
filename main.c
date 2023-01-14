#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#define MAX_SIZE 20

char command[100];
void createfile();
void clear(char ch[]);
void make_dir(char address[]);
void delete_quote(char address[]);

int main()
{
    int flag=1;
    while(flag){
        scanf("%s",command);
        if(!strcmp(command,"exit")){
            printf("Good Luck!");
            flag=0;
        }
        if(!strcmp(command,"createfile")){
            createfile();
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

void delete_quote(char address[]){
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
        delete_quote(address);
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


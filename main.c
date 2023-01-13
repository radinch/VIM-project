#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#define MAX_SIZE 20

char command[50];
void createfile();
void clear(char ch[]);
void make_dir(char address);

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
    int length=strlen(ch);
    for(int i=0;i<length;i++){
        ch[i]="\0";
    }
}

void createfile(){
    char buff[10],address[50];
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid input\n");
        return;
    }
    char ch=getchar();
    ch=getchar();
    gets(address);
    int length=strlen(address);
    if(address[0]=='"' && address[0]=='"'){

    }
    else{
        printf("%s\n",address);
        printf("%d\n",mkdir(address));
    }
}

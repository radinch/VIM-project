#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAX_SIZE 20

char command[50];
void createfile();
void clear(char ch[]);

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
    if(strcmp(buff,"--f")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid Input\n");
        return;
    }
    clear(command);
    gets(address);
    int length=strlen(address);
    if(address[0]=='"' && address[0]=='"'){

    }
    else{
        printf("%d",mkdir(address));
    }
}

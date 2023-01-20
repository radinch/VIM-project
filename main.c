#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#define MAX_SIZE 1000

char command[MAX_SIZE];
char clipboard[MAX_SIZE];

//Main commands
void createfile();
void cat();
void insertstr();
void removestr();
void copystr();
void cutstr();
void pastestr();
void find();

//Auxiliary functions
void clear(char ch[]);
void make_dir(char address[]);
void delete_quote_v1(char address[]);
void input_file_address(char address[]);
void input_string(char string[]);
int check_correctness(char * p,int length,char temp[]);//for checking weather the absolute word is found or not
void check_find_options(int *options,int *n);
int convert_string(char string[]);

int main(){
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

void input_file_address(char address[]){
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

void createfile(){
    char buff[MAX_SIZE],address[MAX_SIZE];
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
    char buff[MAX_SIZE],address[MAX_SIZE];
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
    char buff[MAX_SIZE]={0},address[MAX_SIZE]={0},string[MAX_SIZE]={0};
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-str")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_string(string);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
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
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
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
    char buff[100]={0},address[100]={0};
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
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
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
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
    if(strcmp(buff,"-file")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_file_address(address);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-pos")){
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
    int *options=(int *)malloc(sizeof(int)*4),*n; //just for checking this useless options
    for(int i=0;i<4;i++){
        *(options+i)=0;
    }
    scanf("%s",buff);
    if(strcmp(buff,"-str")){
        char ch[50];
        scanf("%[^\n]%*c",ch);
        printf("Invalid command\n");
        return;
    }
    input_string(string);
    convert_stiring(string);
    clear(buff);
    scanf("%s",buff);
    if(strcmp(buff,"-file")){
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
    check_find_options(options,n);
    FILE * file =fopen(address,"r");
    if(*options==1){
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
        char *p;
        int countChar=0;
        while(fgets(temp,MAX_SIZE,file)!=NULL){
            for(int i=0;i<strlen(temp);i++){
                if(strstr(temp+i,string)!=NULL){
                    char *p=strstr(temp+i,string);
                    int length=strlen(string);
                    if(check_correctness(p,length,temp)){
                        countChar+=p-temp;
                        flag=1;
                        break;
                    }
                }
            }
            if(flag==1){
                break;
            }
            countChar+=strlen(temp);
            clear(temp);
        }
        if(flag==0){
            printf("%d\n",-1);
        }
        else{
            printf("Found: index of the first Character is [%d]\n",countChar);
        }
    }
    fclose(file);
}

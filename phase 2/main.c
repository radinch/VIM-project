#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include "prototypes.h"

WINDOW *win1;
WINDOW * win2;
WINDOW * win3,*win4;
FILE * file;
FILE * file_buff;
FILE * file_open;

int width=0;
int heigth=50;
int mode=0;
void windows(char name[]);
void navigation(char ch);
void save(char name[]);
void open_file(char name[],char buffer[]);
void new_find(char tmp[],char buffer[]);
int check_loc(int n,int find_loc[],int char_loc,int len){
    for(int i=0;i<n;i++){
        if(char_loc>=find_loc[i] && char_loc<find_loc[i]+len){
            return 1;
        }
    }
    return 0;
}

int main()
{
    char buffer[MAX_SIZE]="New file     +";
    file=fopen("file.txt","w");
    file_buff=fopen("file_buff.txt","w");
    initscr();
    refresh();
    noecho();
    start_color();
    windows(buffer);
    refresh();
    int countEnters=1;
    int termination=1;
    int t=1; //avoid printing wrong line numbers
    char command[MAX_SIZE];
    cls(command);
    int count=0;
    int for_name=0;
    char temp[MAX_SIZE];
    char left[MAX_SIZE];
    char right[MAX_SIZE];
    char name[MAX_SIZE];
    char tmp[MAX_SIZE];
    while(termination){
        refresh();
        char c=0;
        int flag=0;
        int flag1=0;
        init_pair(4, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(4) | A_BOLD);
        win4=newwin(1,200,29,0);
        wbkgd(win4,COLOR_PAIR(4));
        attroff(COLOR_PAIR(4) | A_BOLD);
        wrefresh(win4);
        while(mode==0){
            refresh();
            windows(buffer);
            curs_set(1);
            c=getch();
            if(for_name && c!='\n'){
                flag=1;
                int length=strlen(buffer);
                buffer[length]=c;
                wprintw(win4,"%c",c);
                wrefresh(win4);
            }
            else if(flag==1 && c=='\n'){
                flag=0;
                int j=0;
                if(for_name){
                    cls(name);
                    for(int i=1;i<strlen(buffer);i++){
                        name[i-1]=buffer[i];
                    }
                    save(name);
                    for_name=0;
                    file_name_3(name,buffer);
                    //cls(name);
                    //strcat(buffer,"     +");
                    wclear(win2);
                    wrefresh(win2);
                    wprintw(win2,"  %s",buffer);
                    wrefresh(win2);
                    wclear(win4);
                    wrefresh(win4);
                    continue;
                }
                while(command[j]!=' ' && j<=count){
                    left[j]=command[j];
                    j++;
                }
                count=0;
                if(!strcmp(left,"saveas")){
                    cls(right);
                    for(int i=8;i<strlen(command);i++){
                        right[i-8]=command[i];
                    }
                    FILE *new_file=fopen(right,"w");
                    fclose(file_buff);
                    file_buff=fopen("file_buff.txt","r");
                    char ch='a';
                    while(ch!=EOF){
                        ch=getc(file_buff);
                        if(ch!=EOF){
                            putc(ch,new_file);
                        }
                    }
                    strcpy(name,right);
                    file_name_3(right,buffer);
                    //strcat(buffer,"     +");
                    cls(right);
                    fclose(file_buff);
                    fclose(new_file);
                    file_buff=fopen("file_buff.txt","a");
                    wclear(win4);
                    wrefresh(win4);
                    wprintw(win4,"Success");
                    wrefresh(win4);
                    usleep(1000000);
                    wclear(win2);
                    wrefresh(win2);
                    wprintw(win2,"  %s",buffer);
                    wrefresh(win2);
                }
                if(!strcmp(left,"save")){
                    if(strstr(buffer,"New file")!=NULL){
                        cls(buffer);
                        wclear(win4);
                        wrefresh(win4);
                        wprintw(win4,"Please choose a name for your file. ");
                        wrefresh(win4);
                        for_name=1;
                        continue;
                    }
                    else{
                        file_name_3(name,buffer);
                        save(name);
                    }
                }
                if(!strcmp(left,"open")){
                    if(strstr(buffer,"New file")!=NULL){
                        cls(buffer);
                        wclear(win4);
                        wrefresh(win4);
                        wprintw(win4,"Please choose a name for your file. ");
                        wrefresh(win4);
                        char c=0;
                        c=getch();
                        wprintw(win4,"%c",c);
                        wrefresh(win4);
                        while(c!='\n'){
                            c=getch();
                            if(c!='\n'){
                                int length=strlen(buffer);
                                buffer[length]=c;
                                wprintw(win4,"%c",c);
                                wrefresh(win4);
                            }
                        }
                        save(buffer);
                    }
                    else{
                        save(name);
                    }
                    cls(right);
                    for(int i=6;i<strlen(command);i++){
                        right[i-6]=command[i];
                    }
                    open_file(right,buffer);
                    strcpy(name,right);
                    cls(right);
                }
                if(!strcmp(left,"undo")){
                    cls(right);
                    for(int i=6;i<strlen(command);i++){
                        right[i-6]=command[i];
                    }
                    undo(right);
                    strcpy(name,right);
                    cls(right);
                }
                cls(left);
                cls(command);
                wclear(win4);
                wrefresh(win4);
            }
            else if(flag==1){
                command[count]=c;
                count++;
                wprintw(win4,"%c",c);
                wrefresh(win4);
            }
            else if(flag1==1){
                cls(tmp);
                while(c!='\n'){
                    if(c!='\n'){
                        int len=strlen(tmp);
                        tmp[len]=c;
                        wprintw(win4,"%c",c);
                        wrefresh(win4);
                    }
                    c=getch();
                }
                flag1=0;
                wclear(win4);
                wrefresh(win4);
                new_find(tmp,buffer);
                cls(tmp);
            }
            else if(c=='i'){
                mode=1;
            }
            else if(c=='v'){
                mode=2;
            }
            else if(c=='h' || c=='j' || c=='k' || c=='l'){
                navigation(c);
            }
            else if(c==':'){
                flag=1;
                wprintw(win4,"%c",c);
                wrefresh(win4);
            }
            else if(c=='='){
                fclose(file_buff);
                auto_indent("file_buff.txt");
                clear();
                refresh();
                windows(buffer);
                wclear(win4);
                wrefresh(win4);
                int count=1;
                file_buff=fopen("file_buff.txt","r");
                char ch=0;
                printw("%6d ",count);
                while(ch!=EOF){
                    ch=getc(file_buff);
                    if(ch!=EOF && ch!='\n'){
                        printw("%c",ch);
                        refresh();
                    }
                    if(ch=='\n'){
                        count++;
                        int x,y;
                        getyx(stdscr,y,x);
                        move(y+1,0);
                        printw("%6d ",count);
                        refresh();
                    }
                }
                fclose(file_buff);
                file_buff=fopen("file_buff.txt","a");
            }
            else if(c=='/'){
                flag1=1;
                wprintw(win4,"%c",c);
                wrefresh(win4);
            }
            else{
                termination=0;
                break;
            }
        }
        if(mode==1){
            if(strstr(buffer,"+")==NULL){
                strcat(buffer,"     +");
            }
            windows(buffer);
            curs_set(2);
            char ch=0;
            if(t==1){
                ch='\n';
            }
            while(mode==1){
                if(ch=='\n'){
                    attron(A_DIM);
                    if(mode==1){
                        printw("%6d ",countEnters);
                        fprintf(file,"%6d ",countEnters);
                    }
                    attroff(A_DIM);
                }
                ch=getch();
                attron(A_BOLD);
                attroff(A_BOLD);
                if(ch=='\n'){
                    countEnters++;
                    if(countEnters>27){
                        clear();
                        curs_set(0);
                        //move(0,0);
                        refresh();
                        windows(buffer);
                        fclose(file);
                        file=fopen("file.txt","r");
                        char m=0;
                        int n=1;
                        while(m!=EOF){
                            m=getc(file);
                            if(m=='\n'){
                                n++;
                            }
                            if(n>countEnters-27 && m!='\n' && m!=EOF){
                                printw("%c",m);
                                refresh();
                            }
                            if(n>countEnters-27 && m=='\n'){
                                int y,x;
                                getyx(stdscr,y,x);
                                move(y+1,0);
                                //printw("%6d ",count);
                                refresh();
                            }
                        }
                        refresh();
                        fclose(file);
                        curs_set(2);
                        file=fopen("file.txt","a");
                        refresh();
                    }
                }
                if(ch!=27){
                    printw("%c",ch);
                    putc(ch,file);
                    putc(ch,file_buff);
                }
                if(ch==27){
                    mode=0;
                    t=0;
                    break;
                }
                refresh();

            }
        }
        if(mode==2){
            curs_set(1);
            windows(buffer);
            char ch;
            while(mode==2){
                ch=getch();
                if(ch=='h' || ch=='j' || ch=='k' || ch=='l'){
                    navigation(ch);
                }
                if(ch==27){
                    mode=0;
                    break;
                }
            }
        }
    }
    fclose(file);
    fclose(file_buff);
    endwin();
    return 0;
}

void windows(char name[]){
    //clear();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(1) | A_BOLD);
    win1=newwin(1,15,28,0);
    wbkgd(win1,COLOR_PAIR(1));
    if(mode==0){
        wprintw(win1,"    NORMAL");
    }
    else if(mode==1){
        wprintw(win1,"    INSERT");
    }
    else{
        wprintw(win1,"    VISUAL");
    }
    attroff(COLOR_PAIR(1) | A_BOLD);
    wrefresh(win1);
    init_color(COLOR_GREEN,300,300,300);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    attron(COLOR_PAIR(2) | A_BOLD);
    win2=newwin(1,30,28,15);
    wbkgd(win2,COLOR_PAIR(2));
    wprintw(win2,"  %s",name);
    attroff(COLOR_PAIR(2) | A_BOLD);
    wrefresh(win2);
    init_color(COLOR_MAGENTA,250,250,250);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    attron(COLOR_PAIR(3) | A_BOLD);
    win3=newwin(1,200,28,45);
    wbkgd(win3,COLOR_PAIR(3));
    attroff(COLOR_PAIR(3) | A_BOLD);
    wrefresh(win3);
    refresh();

}

void navigation(char ch){
    int x,y;
    getyx(stdscr,y,x);
    int c1=mvinch(y+1,x);
    int c2=mvinch(y,x+1);
    int c3=mvinch(y-1,x);
    int c4=mvinch(y,x-1);
    int c=mvinch(y,x);
    char temp[MAX_SIZE];
    //move(10,10);
    //printw("%d",c);
    if(ch=='h' && x>7){
        move(y,x-1);
        refresh();
    }
    else if(ch=='l' && c2!=32){
        move(y,x+1);
        refresh();
    }
    else if(ch=='k'){
        int f=0;
        /*if(x<4){
            FILE *file=fopen("file.txt","r");
            for(int i=0;i<x;i++){
                fgets(temp,MAX_SIZE,file);
                if(i>)
                    printw("%6d %s",i,temp);
                    refresh();
            }
            fclose(file);
            curs_set(2);
            return;
        }*/
        for(int i=x;i>=7;i--){
            c3=mvinch(y-1,i);
            c=mvinch(y,x);
            if(c3!=32){
                f=1;
                move(y-1,i);
                refresh();
                break;
            }
        }
        if(!f){
            move(y-1,7);
        }
    }
    else if(ch=='j'){
        /*if(x>23){
            fclose(file);
            file=fopen("file.txt","r");
            char m=0;
            int n=1;
            while(m!=EOF){
                m=getc(file);
                if(m=='\n'){
                    n++;
                }
                if(n>x-23 && m!='\n' && m!=EOF){
                    printw("%c",m);
                    refresh();
                }
                if(n>x-23 && m=='\n'){
                    int y,x;
                    getyx(stdscr,y,x);
                    move(y+1,0);
                    //printw("%6d ",count);
                    refresh();
                }
            }
            refresh();
            fclose(file);
            curs_set(2);
            file=fopen("file.txt","a");
            refresh();
            return;
        }*/
        for(int i=x;i>=7;i--){
            c2=mvinch(y+1,i);
            c=mvinch(y,x);
            if(c2!=32){
                move(y+1,i);
                refresh();
                break;
            }
        }
    }
}

void save(char name[]){
    FILE *new_file=fopen(name,"w");
    fclose(file_buff);
    file_buff=fopen("file_buff.txt","r");
    char ch='a';
    while(ch!=EOF){
        ch=getc(file_buff);
        if(ch!=EOF){
            putc(ch,new_file);
        }
    }
    fclose(file_buff);
    fclose(new_file);
    file_buff=fopen("file_buff.txt","a");
    wclear(win4);
    wrefresh(win4);
    wprintw(win4,"Success");
    wrefresh(win4);
    usleep(1000000);
}

void open_file(char name[],char buffer[]){
    char c=0;
    int count=1;
    char temp[MAX_SIZE];
    file_name_3(name,buffer);
    clear();
    windows(buffer);
    wclear(win4);
    wrefresh(win4);
    refresh();
    file_open=fopen(name,"r");
    printw("%6d ",count);
    while(c!=EOF){
        c=getc(file_open);
        if(c!=EOF && c!='\n'){
            printw("%c",c);
            refresh();
        }
        if(c=='\n'){
            count++;
            int x,y;
            getyx(stdscr,y,x);
            move(y+1,0);
            printw("%6d ",count);
            refresh();
        }
    }
    fclose(file_open);
    refresh();
}

void new_find(char tmp[],char buffer[]){
    int *options=(int *)malloc(sizeof(int)*4);
    *(options)=0;
    *(options+1)=0;
    *(options+2)=0;
    *(options+3)=1;
    char locations[MAX_SIZE]={0};
    fclose(file_buff);
    arm_activate=1;
    find("file_buff.txt",tmp,options,1,locations);
    if(locations[0]=='-'){
        file_buff=fopen("file_buff.txt","a");
        return;
    }
    int flag=0;
    int find_loc[MAX_SIZE]={0};
    int count=0;
    for(int i=0;i<strlen(locations)-1;i++){
        if(locations[i]>='0' && locations[i]<='9'){
            flag=1;
            find_loc[count]=find_loc[count]*10 + (locations[i]-48);
        }
        if(locations[i]==' '){
            flag=0;
            count++;
        }
    }
    clear();
    windows(buffer);
    wclear(win4);
    wrefresh(win4);
    refresh();
    file_buff=fopen("file_buff.txt","r");
    int counter=1;
    printw("%6d ",counter);
    int char_number=0;
    char c=0;
    while(c!=EOF){
        c=getc(file_buff);
        char_number++;
        if(c!=EOF && c!='\n'){
            if(check_loc(count+1,find_loc,char_number-1,strlen(tmp))){
                init_pair(5, COLOR_RED, COLOR_BLACK);
                attron(COLOR_PAIR(5) | A_BOLD);
                printw("%c",c);
                refresh();
                attroff(COLOR_PAIR(5) | A_BOLD);
            }
            else{
                printw("%c",c);
                refresh();
            }
        }
        if(c=='\n'){
            counter++;
            int x,y;
            getyx(stdscr,y,x);
            move(y+1,0);
            printw("%6d ",counter);
            refresh();
        }
    }
    fclose(file_buff);
    windows(buffer);
    c=getch();
    if(c!='n'){
        clear();
        refresh();
        windows(buffer);
        wclear(win4);
        wrefresh(win4);
        int count=1;
        file_buff=fopen("file_buff.txt","r");
        char ch=0;
        printw("%6d ",count);
        while(ch!=EOF){
            ch=getc(file_buff);
            if(ch!=EOF && ch!='\n'){
                printw("%c",ch);
                refresh();
            }
            if(ch=='\n'){
                count++;
                int x,y;
                getyx(stdscr,y,x);
                move(y+1,0);
                printw("%6d ",count);
                refresh();
            }
        }
        //else{

        //}
        fclose(file_buff);
        file_buff=fopen("file_buff.txt","a");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include "prototypes.h"
int width=0;
int heigth=50;
int mode=0;
void windows();
void navigation(char ch);
int main()
{
    FILE *file=fopen("file.txt","w");
    FILE *file_buff=fopen("file_buff.txt","w");
    FILE *f=fopen("root/file.txt","w");
    fclose(f);
    initscr();
    refresh();
    noecho();
    start_color();
    windows();
    refresh();
    int countEnters=1;
    int termination=1;
    int t=1; //avoid printing wrong line numbers
    char command[MAX_SIZE];
    cls(command);
    int count=0;
    char temp[MAX_SIZE];
    char left[MAX_SIZE];
    char right[MAX_SIZE];
    while(termination){
        refresh();
        char c=0;
        int flag=0;
        init_pair(4, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(4) | A_BOLD);
        WINDOW *win4=newwin(1,200,29,0);
        wbkgd(win4,COLOR_PAIR(4));
        attroff(COLOR_PAIR(4) | A_BOLD);
        wrefresh(win4);
        while(mode==0){
            refresh();
            windows();
            curs_set(1);
            c=getch();
            if(flag==1 && c=='\n'){
                flag=0;
                int j=0;
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
                    cls(right);
                    fclose(file_buff);
                    fclose(new_file);
                    file_buff=fopen("file_buff.txt","a");

                    wclear(win4);
                    wrefresh(win4);
                    wprintw(win4,"Success");
                    wrefresh(win4);
                    usleep(1000000);
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
            else if(c=='i'){
                mode=1;
            }
            else if(c=='v'){
                mode=2;
            }
            else if(c=='h' || c=='j' || c=='k' || c=='l'){
                navigation(c);
            }
            else if(c==':' || c=='/'){
                flag=1;
                wprintw(win4,"%c",c);
                wrefresh(win4);
            }
            else{
                termination=0;
                break;
            }
        }
        if(mode==1){
            windows();
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
                        windows();
                        fclose(file);
                        file=fopen("file.txt","r");
                        char m=0;
                        int n=1;
                        while(m!=EOF){
                            m=getc(file);
                            if(m=='\n'){
                               n++;
                            }
                            if(n>countEnters-27)
                            printw("%c",m);
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
            windows();
            char ch;
            while(mode==2){
                ch=getch();
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

void windows(){
    //clear();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(1) | A_BOLD);
    WINDOW *win1=newwin(1,15,28,0);
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
    WINDOW * win2=newwin(1,30,28,15);
    wbkgd(win2,COLOR_PAIR(2));
    wprintw(win2,"  New file.txt");
    attroff(COLOR_PAIR(2) | A_BOLD);
    wrefresh(win2);
    init_color(COLOR_MAGENTA,250,250,250);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    attron(COLOR_PAIR(3) | A_BOLD);
    WINDOW * win3=newwin(1,200,28,45);
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
    if(ch=='h' && x>7 && c4!=32){
        move(y,x-1);
        refresh();
    }
    else if(ch=='l' && c2!=32){
        move(y,x+1);
        refresh();
    }
    else if(ch=='k'){
        int f=0;
        if(x>24){
            FILE *file=fopen("file.txt","r");
            for(int i=0;i<x;i++){
                fgets(temp,MAX_SIZE,file);
                if(i>x-24)
                    printw("%6d %s",i,temp);
                    refresh();
            }
            fclose(file);
            curs_set(2);
            return;
        }
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

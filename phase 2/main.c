#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#define MAX_SIZE 1000
int width=0;
int heigth=50;
int mode=0;
void windows();
void navigation(char ch);

int main()
{
    FILE *file=fopen("file.txt","w");
    initscr();
    refresh();
    noecho();
    start_color();
    windows();
    refresh();
    long countEnters=1;
    int termination=1;
    int t=1; //avoid printing wrong line numbers
    char temp[MAX_SIZE];
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
                wclear(win4);
                wrefresh(win4);
            }
            else if(flag==1){
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
                    }
                    attroff(A_DIM);
                }
                ch=getch();
                attron(A_BOLD);
                if(ch!=27){
                    printw("%c",ch);
                    putc(ch,file);
                }
                attroff(A_BOLD);
                if(ch=='\n'){
                    countEnters++;
                    if(countEnters>27){
                        //clear();
                        curs_set(0);
                        move(0,0);
                        refresh();
                        windows();
                        fclose(file);
                        file=fopen("file.txt","r");
                        for(int i=0;i<countEnters;i++){
                            fgets(temp,MAX_SIZE,file);
                            if(i>countEnters-27)
                                printw("%6d %s",i,temp);
                                refresh();
                        }
                        fclose(file);
                        curs_set(2);
                        file=fopen("file.txt","a");
                    }
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

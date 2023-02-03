#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
int width=0;
int heigth=50;
int mode=0;
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
    wprintw(win2,"  file_name.txt");
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
int main()
{
    initscr();
    refresh();
    noecho();
    start_color();
    windows();
    refresh();
    long countEnters=1;
    int termination=1;
    int t=1; //avoid printing wrong line numbers
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
            curs_set(0);
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
                if(ch!=27)
                    printw("%c",ch);
                attroff(A_BOLD);
                if(ch=='\n'){
                    countEnters++;
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
            curs_set(0);
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
    endwin();
    return 0;
}

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int key = 0;

int h=0, w=0;

int get_input_simbol()
{
    int i = getch();
    int x0, y0;
    getyx(stdscr, x0, y0);
    move(x0, y0 - 1);
    delch();
    return i;
}

void draw(int a[h][w])
{
    for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                move(i, j);
                if (a[i][j] == 1)
                    printw("*");
            }
        }
}

void life(int a[h][w])
{
    int b[h][w];
    int c = 0;

    while (1)
    {
        for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            b[i][j] = 0;
        
        for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            b[i][j] = a[i][j];

        getch();
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int count = 0;
                if (a[i-1][j-1] == 1) count++;
                if (a[i][j-1] == 1) count++;
                if (a[i+1][j-1] == 1) count++;

                if (a[i-1][j] == 1) count++;
                if (a[i+1][j] == 1) count++;

                if (a[i-1][j+1] == 1) count++;
                if (a[i][j+1] == 1) count++;
                if (a[i+1][j+1] == 1) count++;

                if (a[i][j] == 1)
                {
                    if (count < 2 || count > 3)
                        b[i][j] = 0;
                }
                else
                {
                    if (count == 3)
                        b[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
                a[i][j] = 0;
        
        for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            a[i][j] = b[i][j];

        erase();
        draw(a);
        c++;
        move(0, 0);
        printw("%d", c);
        refresh();
    }
}

int main(){
    initscr();
    h = getmaxy(stdscr);
    w = getmaxx(stdscr);
    int a[h][w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            a[i][j] = 0;
        

    int key = 0;
    int x=0, y=0;
    while (key != 'q')
    {
        key = get_input_simbol();

        switch (key)
        {
        case 'w':
        if (y>0)
            y--;
            break;
        case 'd':
        if (x<h)
            x++;
            break;
        case 's':
        if (y<w)
            y++;
            break;
        case 'a':
        if (x>0)
            x--;
            break;
        default:
            break;
        }

        if (key == '=')
            a[y][x] = (a[y][x]==0? 1 : 0);
        
        erase();
        if (key == '-')
        {
            life(a);
        }

        draw(a);

        move(y, x);
        refresh();
    }
    getch();

    endwin();
	return 0;
}
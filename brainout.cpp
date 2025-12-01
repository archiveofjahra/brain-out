#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int KOLOM;
int BARIS;


void kotak_border() {
    attron(COLOR_PAIR(5) |A_BOLD);

    for (int i = 0; i < KOLOM; i++) {
        mvaddch(0, i, '-');
        mvaddch(BARIS - 1, i, '-');
    }
    for (int j = 0; j < BARIS; j++) {
        mvaddch(j, 0, '|');
        mvaddch(j, KOLOM - 1, '|');
    }
    

    mvaddch(0, 0, '+');
    mvaddch(0, KOLOM - 1, '+');
    mvaddch(BARIS - 1, 0, '+');
    mvaddch(BARIS - 1, KOLOM - 1, '+');

    attroff(COLOR_PAIR(5) |A_BOLD);
}
void teks_tengah(int y, const char *text) {
    int x = (KOLOM - (int)strlen(text)) / 2;
    mvprintw(y, x, "%s", text);
}

void efek_ketik(int y, int x, const char *text, int speed) {
    for (int i = 0; i < (int)strlen(text); i++) {
        mvaddch(y, x + i, text[i]);
        refresh();
        napms(speed);
    }
}
void loading_next(int Level) {
    clear();
    kotak_border();

    char buf[50];
    sprintf(buf, "Next = %d", Level);
    mvprintw(BARIS - 2, KOLOM - strlen(buf) - 3, "%s", buf);

    const char *teks = "GOOD JOB...YOU GREAT...";

    for (int i = 0; i < 3; i++) {
        mvprintw(BARIS / 2, (KOLOM - (int)strlen(teks)) / 2, "%s", teks);

        for (int j = 0; j <= i; j++)
            printw(".");

        refresh();
        napms(400);
        clear();
        kotak_border();
    }
}

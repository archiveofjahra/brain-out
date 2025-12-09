#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int KOLOM;
int BARIS;

void kotak_border() {
    attron(COLOR_PAIR(2) |A_BOLD);
    for (int i = 0; i < KOLOM; i++) {
        mvaddch(0, i, '-');
        mvaddch(BARIS - 1, i, '-');
    }
    attron(COLOR_PAIR(1) | A_BOLD);
    for (int j = 0; j < BARIS; j++) {
        mvaddch(j, 0, '|');
        mvaddch(j, KOLOM - 1, '|');
    attron(COLOR_PAIR(1) | A_BOLD);
    }
    mvaddch(0, 0, '+');
    mvaddch(0, KOLOM - 1, '+');
    mvaddch(BARIS - 1, 0, '+');
    mvaddch(BARIS - 1, KOLOM - 1, '+');
    attroff(COLOR_PAIR(1) |A_BOLD);
}
void teks_tengah(int y, const char *text) {
    int x = (KOLOM - (int)strlen(text)) / 2;
    mvprintw(y, x, "%s", text);
}

void efek_ketik(int y, int x, const char *text, int speed) {
        int colors[] = {1, 2, 4, 5};
        int len = (int)strlen(text);
    for (int i = 0; i < (int)strlen(text); i++) {
        int cp = colors[i % 4];
    attron(COLOR_PAIR(cp) | A_BOLD);
        mvaddch(y, x + i, text[i]);
    attroff(COLOR_PAIR(cp) | A_BOLD);
    refresh();
    napms(speed);
    }
}
void loading_next(int Level) {
    clear();
    getmaxyx(stdscr, BARIS, KOLOM);
    kotak_border();

    char buf[50];
    sprintf(buf, "Next = %d", Level);
    mvprintw(BARIS - 2, KOLOM - (int)strlen(buf) - 3, "%s", buf);

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

void tampil_timer(int t) {
    if (t <= 10) {
        attron(COLOR_PAIR(3) | A_BOLD);
        beep();
    } else {
        attron(COLOR_PAIR(4));
    }
    mvprintw(1, KOLOM - 15, "WAKTU: %02d", t);
    attroff(COLOR_PAIR(3) | A_BOLD);
    attroff(COLOR_PAIR(4));
}

void showCaraBermain() {
    clear();
    getmaxyx(stdscr, BARIS, KOLOM);
    kotak_border();
    attron(COLOR_PAIR(1) | A_BOLD);
    teks_tengah(2, "CARA BERMAIN");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(5, 4, "1. Setiap soal punya waktu 15 detik");
    mvprintw(6, 4, "2. Jawab sebelum waktu habis");
    mvprintw(7, 4, "3. Salah = game over");
    mvprintw(8, 4, "4. pilih jawaban dan ikuti intruksi");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    attron(COLOR_PAIR (1) | A_BLINK | A_BOLD);
    teks_tengah(BARIS - 3, ">> SIAP = SPASI <<");
    attroff(A_BLINK | A_BOLD);
    while (getch() != ' ');
}

int menuPilihLevel() {
    int ch = 0;
    while (1) {
        clear();
        kotak_border();

        attron(COLOR_PAIR(5) | A_BOLD);
        teks_tengah(2, "PILIH LEVEL");

        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(5, 6, "1. Level Symbol ");
        mvprintw(6, 6, "2. Level Umum ");
        mvprintw(9, 6, "Pilih level : ");

        refresh();
        ch = getch();
        if (ch == '1') return 1;
        if (ch == '2') return 2;
    }
}

int tanya_lanjut() {
    clear(); 
    kotak_border();
    attron(COLOR_PAIR(2) | A_BOLD);
    teks_tengah(5, "LEVEL SELESAI 100%!");
    attroff(COLOR_PAIR(2) | A_BOLD);

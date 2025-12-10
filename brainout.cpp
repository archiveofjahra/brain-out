#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int KOLOM;
int BARIS;

void kotak_border() {
    attron(COLOR_PAIR(2) | A_BOLD);
    for (int i = 0; i < KOLOM; i++) {
    mvaddch(0, i, '-');
    mvaddch(BARIS - 1, i, '-');
}
attroff(COLOR_PAIR(2) | A_BOLD);

    attron(COLOR_PAIR(1) | A_BOLD);
    for (int j = 0; j < BARIS; j++) {
        mvaddch(j, 0, '|');
        mvaddch(j, KOLOM - 1, '|');
    }
    attroff(COLOR_PAIR(1) | A_BOLD);
    
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
        int len = strlen(text);
        for (int i = 0; i < len; i++) {
            
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
    attron(COLOR_PAIR(1) | A_BOLD);
    sprintf(buf, "Next LEVEL %d", Level);
    mvprintw(BARIS - 2, KOLOM - (int)strlen(buf) - 3, "%s", buf);

    const char *teks = "GOOD JOBBB....YOUR GREATTT........";
    
    attron(COLOR_PAIR(3) | A_BOLD);
    efek_ketik(LINES / 3, (COLS - (int)strlen(teks)) / 2, teks, 70);
    attroff(COLOR_PAIR(3) | A_BOLD);

        refresh();
        napms(700);

}

void tampil_timer(int t) {
    if (t <= 10) {
        attron(COLOR_PAIR(3) | A_BOLD);
        beep();
    } else {
        attron(COLOR_PAIR(2) | A_BOLD);
    }
    mvprintw(1, KOLOM - 15, "WAKTU: %02d", t);
    attroff(COLOR_PAIR(3) | A_BOLD);
    attroff(COLOR_PAIR(2) | A_BOLD);
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
    teks_tengah(22, ">> SUDAH SIAP = SPASI & ENTER <<"); 
    attroff(A_BLINK | A_BOLD);

    int ch;
    while ((ch = getch()) != ' ');
    while ((ch = getch()) != '\n' && ch != 10);
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

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(8, 6, "Lanjut level berikutnya? (y/n): ");
    refresh();

    int ch;
    while ((ch =tolower(getch())) != 'y' && ch != 'n');
    return (ch == 'y');  
}

int main() {
    initscr();
    getmaxyx(stdscr, BARIS, KOLOM);
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);

    if (has_colors()) {
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_GREEN, COLOR_BLACK);
    }

    srand((unsigned)time(NULL));

    char nama[50];
    int row, col;
    getmaxyx(stdscr, row, col);

    clear();
    kotak_border();

    attron(COLOR_PAIR(1) | A_BOLD);
    char judul[] = "=== SELAMAT DATANG DI BRAIN OUT ===";
    efek_ketik(3, (col - (int)strlen(judul)) / 2, judul, 50);
    attroff(COLOR_PAIR(1) | A_BOLD);

    napms(500);

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(5, 5, "Masukkan nama kamu: ");
    echo();
    curs_set(1);
    move(5, 27);
    getstr(nama);
    noecho();
    curs_set(0);
    attroff(COLOR_PAIR(1) | A_BOLD);

    clear(); 
    kotak_border();

    char sapaan[100];
    sprintf(sapaan, "HALO %s! SUDAH SIAP? JAWABLAH PERTANYAAN DENGAN BENAR!", nama);
    efek_ketik(5, 5, sapaan, 60);

    attron(COLOR_PAIR (5) | A_BLINK | A_BOLD);
    teks_tengah(22, ">> SPASI UNTUK MULAI <<"); 
    attroff(A_BLINK | A_BOLD);
    while (getch() != ' ');

    showCaraBermain();
    int level = menuPilihLevel();

    clear();
    kotak_border();
    attron(COLOR_PAIR(2) | A_BOLD);
    efek_ketik(LINES / 3, (COLS - 20) / 2, "LETSSGOOOOO........", 70);
    attroff(COLOR_PAIR(2));
    napms(800);

    clear();
    kotak_border();
    attron(COLOR_PAIR(2) | A_BOLD);
     efek_ketik(LINES / 3, (COLS - 20) / 2, "LOADINGGG........", 70);
    attroff(COLOR_PAIR(2) | A_BOLD);
    napms(1500);
    refresh();
    napms(1500);
    clear();

    const char *soal_Symbol[4] = {
        "Simbol apakah ini?",
        "Yang manakah simbol INPUT / OUTPUT?",
        "Manakah simbol Decision?",
        "Apakah gambar simbol dibawah ini STORAGE SYMBOL?"
    };

    const char *soal_Umum[5] = {
        "Fungsi mulai ncurses adalah?",
        "Cetak di posisi dinamakan?",
        "Disebut apa Delay milidetik?",
        "Fungsi Hapus layar dalam ncurses adalah?",
        "untuk membaca 1 karakter?"
    };

    const char *kunci_Umum[5] = {
        "initscr", "mvprintw", "napms", "clear", "getch"
    };

    int skor_total = 0;
    int gameOver = 0;

    while (level <= 2 && !gameOver) {
        int jumlahSoal = (level == 1) ? 4 : 5;
        const char **soal = (level == 1) ? soal_Symbol : soal_Umum;
        const char **kunciArr = (level == 2) ? kunci_Umum : NULL;

        int skor = 0;
    
        for (int i = 0; i < jumlahSoal; i++) {
            int pos = rand() % 2; 

            clear();
            kotak_border();
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(2, 4, "LEVEL %d - Soal %d/%d", level, i + 1, jumlahSoal);

            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(5, 4, "%s", soal[i]);
             attroff(COLOR_PAIR(1) | A_BOLD);
            
            const char *jBenar = NULL;

            if (level == 1) {
                attron(COLOR_PAIR(5) | A_BOLD);
                int xmid = (KOLOM - 40) / 2;

                if (i == 0) {
                    mvprintw(6, xmid + 10, " _________");
                    mvprintw(7, xmid + 10, "|         |");
                    mvprintw(8, xmid + 10, "|         |");
                    mvprintw(9, xmid + 10, "|_________|");

                    mvprintw(12, xmid - 5, "[A] PROSES");
                    mvprintw(12, xmid + 26, "[L] INPUT/OUTPUT");
                }
                else if (i == 1) {
                    mvprintw(8, xmid - 10, "[A] BELAH KETUPAT");
                    mvprintw(10, xmid - 10, "      /\\");
                    mvprintw(11, xmid - 10, "     /  \\");
                    mvprintw(12, xmid - 10, "     \\  /");
                    mvprintw(13, xmid - 10, "      \\/");

                    mvprintw(8, xmid + 26, "[L] JAJAR GENJANG");
                    mvprintw(10, xmid + 26, "   _________");
                    mvprintw(11, xmid + 26, "  /         /");
                    mvprintw(12, xmid + 26, " /         /");
                    mvprintw(13, xmid + 26, "/_________/");
                }
                else if (i == 2) {
                    mvprintw(8, xmid - 10, "[L] PERSEGI");
                    mvprintw(10, xmid - 10, "   _______");
                    mvprintw(11, xmid - 10, "  |       |");
                    mvprintw(12, xmid - 10, "  |       |");
                    mvprintw(13, xmid - 10, "  |_______|");

                    mvprintw(8, xmid + 30, "[A] BELAH KETUPAT");
                    mvprintw(10, xmid + 33, "      /\\");
                    mvprintw(11, xmid + 33, "     /  \\");
                    mvprintw(12, xmid + 33, "     \\  /");
                    mvprintw(13, xmid + 33, "      \\/");

                    mvprintw(15,  xmid + 9, "[N] TRAPESIUM TERBALIK");
                    mvprintw(16,  xmid + 14, "  ________");
                    mvprintw(17, xmid + 14, " \\        /");
                    mvprintw(18, xmid + 14, "  \\______/");
                }
                else if (i == 3) {
                    mvprintw(6, xmid + 15, "__________");
                    mvprintw(7, xmid + 15, "\\        /");
                    mvprintw(8, xmid + 15, " \\      /");
                    mvprintw(9, xmid + 15, "  \\    /");
                    mvprintw(10, xmid + 15, "   \\  /");
                    mvprintw(11, xmid + 15, "    \\/");

                    mvprintw(14, xmid - 2, "[A] BENAR");
                    mvprintw(14, xmid + 28, "[L] SALAH");
                }

                attroff(COLOR_PAIR(5) | A_BOLD);
            }
            else if (level == 2) {
                int xmid = KOLOM / 2;

                jBenar = kunciArr[i];

                const char *pilihanSalah[] = {
                    "int main", "cout", "sleep", "refresh", "cin"
                };
                const char *jSalah = pilihanSalah[i % 7];
                
               if (pos == 0) {
                attron(COLOR_PAIR(10) | A_BOLD);
                mvprintw(10, xmid - 20, "[A] %s", jBenar);
                mvprintw(10, xmid + 10, "[L] %s", jSalah);
                attroff(COLOR_PAIR(10) | A_BOLD);
    } else {
                attron(COLOR_PAIR(10) | A_BOLD);
                mvprintw(10, xmid - 20, "[A] %s", jSalah);
                mvprintw(10, xmid + 10, "[L] %s", jBenar);
                attroff(COLOR_PAIR(10) | A_BOLD);
   }
            }          
            refresh();

            int waktu = 15;
            int terjawab = 0;
            char jawaban[10] = {0};

            timeout(1000);

            for (int t = waktu; t > 0 && !terjawab; t--) {
                tampil_timer(t);
                refresh();

               int c = getch();

                if (c != ERR) {
                    if (c == 'a' || c == 'A' || c == 'l' || c == 'L' || c == 'n' || c == 'N') {
                        jawaban[0] = tolower(c);
                        jawaban[1] = '\0';
                        terjawab = 1;
                    }
                }
            }

            timeout(-1);

            if (!terjawab) {
                attron(COLOR_PAIR(3) | A_BOLD);
                teks_tengah(BARIS - 4, "WAKTU HABIS! GAME OVER");
                attroff(COLOR_PAIR(3) | A_BOLD);
                refresh();
                napms(1500);
                gameOver = 1;
                break;
            }

            int benar = 0;

            if (level == 1) {
                if (i == 0) benar = (jawaban[0] == 'a');
                if (i == 1) benar = (jawaban[0] == 'l');
                if (i == 2) benar = (jawaban[0] == 'a');
                if (i == 3) benar = (jawaban[0] == 'a');
            }
           else if (level == 2) {
            if ((pos == 0 && jawaban[0] == 'a') ||
                 (pos == 1 && jawaban[0] == 'l')) {
                 benar = 1;
                }

            }

            if (benar) {
                skor++;
                attron(COLOR_PAIR(2) | A_BOLD);
                teks_tengah(BARIS - 4, "BENAR!");
                attroff(COLOR_PAIR(2) | A_BOLD);
                refresh();
                napms(700);
            }

            else {
                attron(COLOR_PAIR(3) | A_BOLD);
                teks_tengah(BARIS - 4, "SALAH! GAME OVER");
                attroff(COLOR_PAIR(3) | A_BOLD);
                refresh();
                napms(1000);
                gameOver = 1;
                break;
            }
        }

        skor_total += skor;

        if (gameOver) break;
         if (level == 2) break;

        loading_next(level + 1);

         if (!tanya_lanjut())
        break;
    
    gameOver = 0;

    level++;

    }

    clear();
    kotak_border();

    attron(COLOR_PAIR(1) | A_BOLD);
    teks_tengah(6, "GAME SELESAI!");

    attron(COLOR_PAIR(2) | A_BOLD);
    char hasil[100];
    sprintf(hasil, "Skor Total: %d", skor_total);
    teks_tengah(9, hasil);
    
    attron(COLOR_PAIR(3) | A_BOLD);
    teks_tengah(11, "LEBIH GIAT LAGI YAAAAA!!!!!");

    teks_tengah(14, "TERIMA KASIH SUDAH BERMAIN!");

    refresh();
    napms(3000);
    sleep(2);

    endwin();
    return 0;
}

#include <ncurses.h>

void print_menu(int highlight) {
    char *menu[] = {"Nhap f(x)", "Tinh f(x) tai 1 diem", "Tinh gan dung tich phan voi sai so cho truoc(mac dinh e<1e-4)", "Thoat chuong trinh", "Lam sach man hinh"};
    int num_choices = sizeof(menu) / sizeof(char *);

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything

    for (int i = 0; i < num_choices; i++) {
        if (highlight == i + 1) {
            attron(A_REVERSE);
            printw("%s\n", menu[i]);
            attroff(A_REVERSE);
        } else {
            printw("%s\n", menu[i]);
        }
    }

    refresh();
}

#include <ncurses.h>

char *menu[] = {"Option 1", "Option 2", "Option 3", "Exit"};
int num_choices = sizeof(menu) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight) {
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < num_choices; ++i) {
        if(highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", menu[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", menu[i]);
        ++y;
    }
    wrefresh(menu_win);
}

int main() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();	// Line buffering disabled. pass on everything
    menu_win = newwin(num_choices + 4, 20, 2, 2);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight);
    while(1) {
        c = wgetch(menu_win);
        switch(c) {
        case KEY_UP:
            if(highlight == 1)
                highlight = num_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if(highlight == num_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0)	// User did a choice come out of the infinite loop
            break;
    }
    mvprintw(num_choices + 5, 0, "You chose choice %d with choice string %s\n", choice, menu[choice - 1]);
    clrtoeol();
    refresh();
    endwin();
    return 0;
}
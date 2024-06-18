#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "xuly.h"
#include "menu.h"
#include "tichphan.h"
#define var_count 1

char *menu[][2] = {
    {"Nhap f(x)", "Nhap du lieu tu file txt"},
    {"Tinh f(x) tai 1 diem", ""},
    {"Tinh gan dung tich phan voi sai so cho truoc", ""},
    {"Thoat chuong trinh", ""},
    {"Lam sach", ""}
};


// Step 2: Update the print_menu function
void print_menu(int highlight_row, int highlight_col) {
    int num_choices = sizeof(menu) / sizeof(menu[0]);

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything

    for (int i = 0; i < num_choices; i++) {
        for (int j = 0; j < 2; j++) {
            if (highlight_row == i && highlight_col == j) {
                attron(A_REVERSE);
                printw("%-30s", menu[i][j]);
                attroff(A_REVERSE);
            } else {
                printw("%-30s", menu[i][j]);
            }
        }
        printw("\n");
    }

    refresh();
}
void print_submenu_select_pp(int highlight) {
    char *menu[] = {"Phuong phap hinh thang", "Phuong phap Simpson"};
    int num_choices = sizeof(menu) / sizeof(char *);
    initscr();
    clear();
    noecho();
    cbreak(); 

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
void get_input_string(char* prompt, char* buffer, int buffer_size) {
    printw("%s", prompt);  // Use printw instead of printf
    echo();  // Enable echoing of input characters
    getnstr(buffer, buffer_size - 1);  // Use getnstr instead of fgets
    noecho();  // Disable echoing
}

float get_input_float(char* prompt) {
    char buffer[50];
    printw("%s", prompt);  // Use printw instead of printf
    echo();  // Enable echoing of input characters
    getnstr(buffer, sizeof(buffer) - 1);  // Use getnstr instead of fgets
    noecho();  // Disable echoing
    float value = atof(buffer);  // Convert string to float
    return value;
}

void handle_option_1() {
    get_input_string("Nhap f(x): ", function, sizeof(function));
    sleep(1);
}

void handle_option_2() {
    function[strcspn(function, "\n")] = 0;
    if (function[0] != '\0') {
        x = get_input_float("Nhap diem can tinh: ");
        const char *expression = function;
        double result = parse_expression(&expression, vars, var_count);
        printw("f(%lf) = %lf\n", x, result);
        refresh();
        sleep(1);
        flag2 = 1;
    } else {
        printw("Ban chua nhap ham so\n");
        refresh();
        sleep(1);
    }
}

void handle_option_3() {
    if (function[0] != '\0') {
        a = get_input_float("Nhap a: ");
        b = get_input_float("Nhap b: ");
        e = get_input_float("Nhap sai so: ");
        const char *expression = function;
        double result;

        // Print submenu
        int sub_choice = 1;
        print_submenu_select_pp(sub_choice);
        int c;
        int old_choice = sub_choice;
        bool exit_loop = false;
        while (!exit_loop) {
            c = getch();
            switch (c) {
                case KEY_UP: 
                    if (sub_choice == 1)
                        sub_choice = 2;
                    else
                        --sub_choice;
                    break;
                case KEY_DOWN:
                    if (sub_choice == 2)
                        sub_choice = 1;
                    else 
                        ++sub_choice;
                    break;
                case '\n':
                    switch (sub_choice) {
                        case 1:
                            result = integrate_trap(a, b, e, expression);
                            flag3 = 1;
                            break;
                        case 2:
                            result = integrate_simp(a, b, e, expression); // Assuming you have this function
                            flag3 = 2;
                            break;
                    }
                    exit_loop = true;
                    break;
            }
            if (old_choice != sub_choice) {
                print_submenu_select_pp(sub_choice);
                old_choice = sub_choice;
            }
        }

        printw("Tich phan cua f(x) tren [%f, %f] la: %lf\n", a, b, result);
        refresh();
        sleep(1);
    } else {
        printw("Ban chua nhap ham so\n");
        refresh();
        sleep(1);
    }
}
void handle_option_6(){
    char filename[100];
    get_input_string("Nhap ten file: ", filename, sizeof(filename));
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printw("Khong the mo file\n");
        refresh();
        sleep(1);
        return;
    }
    fgets(function, sizeof(function), file);
    fclose(file);
    return;
}
void exit_program() {
    endwin();
    exit(0);
}
void reset() {
    clear();
    function[0] = '\0';
    flag2 = 0;
    flag3 = 0;
    refresh();

}
void (*handlers[5][2])() = {
    {handle_option_1, handle_option_6},
    {handle_option_2, NULL},
    {handle_option_3, NULL},
    {exit_program, NULL},
    {reset, NULL}
};
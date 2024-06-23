#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "phu.h"
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
    char log_message[100];
    sprintf(log_message, "f(x) = %s", function);
    write_log(log_message);
    flag2 = 0;
    flag3 = 0;
    sleep(1);
}

void handle_option_2() {
    function[strcspn(function, "\n")] = 0;
    if (function[0] != '\0') {
        x = get_input_float("Nhap diem can tinh: ");
        const char *expression = function;
        double result = parse_expression(&expression, vars, var_count);
        char log_message[100];
        sprintf(log_message, "f(%lf) = %lf", x, result);
        write_log(log_message);
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
        if (!a_entered) {
            a = get_input_float("Nhap a: ");
            a_entered = true;
        }
        if (!b_entered) {
            b = get_input_float("Nhap b: ");
            b_entered = true;
        }
        if (!e_entered) {
            e = get_input_float("Nhap sai so: ");
            e_entered = true;
        }
        if (!precision_entered) {
            precision = get_input_float("Nhap so chu so thap phan: ");
            precision_entered = true;
        }
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
                            flag3 = 1;
                            result = integrate(a, b, e, expression, flag3, precision); // Assuming you have this function
                            res_tichphan = result;
                            break;
                        case 2:
                            flag3 = 2;
                            result = integrate(a, b, e, expression, flag3, precision); // Assuming you have this function
                            res_tichphan = result;
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

void handle_option_6() {
    char filename[100];
    char line[256];
    get_input_string("Nhap ten file: ", filename, sizeof(filename));
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printw("Khong the mo file\n");
        refresh();
        sleep(1);
        return;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        // Loại bỏ ký tự xuống dòng cuối cùng nếu có
        line[strcspn(line, "\n")] = 0;
        remove_spaces(line);
        if (strncmp(line, "f(x)=", 5) == 0) {
            // Sao chép phần còn lại của dòng sau "f(x) ="
            strncpy(function, line + 5, sizeof(function) - 1);
        } else if (strncmp(line, "a=", 2) == 0) {
            sscanf(line + 2, "%lf", &a);
            a_entered = true;
        } else if (strncmp(line, "b=", 2) == 0) {
            sscanf(line + 2, "%lf", &b);
            b_entered = true;
        } else if (strncmp(line, "e=", 2) == 0) {
            sscanf(line + 2, "%lf", &e);
            e_entered = true;
        } else if (strncmp(line, "precision=", 10) == 0) {
            sscanf(line + 10, "%d", &precision);
            precision_entered = true;
        }
    }
    fclose(file);
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
    a_entered = false;
    b_entered = false;
    e_entered = false;
    refresh();
}
void (*handlers[5][2])() = {
    {handle_option_1, handle_option_6},
    {handle_option_2, NULL},
    {handle_option_3, NULL},
    {exit_program, NULL},
    {reset, NULL}
};
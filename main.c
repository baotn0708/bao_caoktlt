// #include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "menu.h"
#include "xuly.h"

char function[100];
float x;
float a, b, e;
int flag2 = 0, flag3 = 0;

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
    if (function[0] != '\0'){
        x = get_input_float("Nhap diem can tinh: ");
        printw("%lf\n",calculate_polynomial(function, x));
        refresh();
        sleep(1);
        flag2 = 1;
    }
    else{
        printw("Ban chua nhap ham so\n");
        refresh();
        sleep(1);
    }
}

void handle_option_3() {
    if (function[0] != '\0'){
        a = get_input_float("Nhap a: ");
        b = get_input_float("Nhap b: ");
        e = get_input_float("Nhap sai so: ");
        printw("Tich phan cua f(x) tren [%f, %f] la: %lf\n", a, b, integrate_trap(a, b, e, function));
        refresh();
        sleep(1);
        flag3 = 1;
    }
    else{
        printw("Ban chua nhap ham so\n");
        refresh();
        sleep(1);
    }
}

int main() {
    int choice = 1;
    int c;

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything
    keypad(stdscr, TRUE);

    print_menu(choice);
    refresh();
    while (1) {
        c = getch(); // Use ncurses getch instead of getchar
        switch (c) {
            case KEY_UP: 
                if (choice == 1)
                    choice = 5;
                else
                    --choice;
                break;
            case KEY_DOWN:
                if (choice == 5)
                    choice = 1;
                else 
                    ++choice;
                break;
            case '\n':
                switch (choice) {
                    case 1:
                        handle_option_1();
                        break;
                    case 2:
                        handle_option_2();
                        break;
                    case 3:
                        handle_option_3();
                        break;
                    case 4:
                        endwin();
                        return 0; // Exit the program
                    case 5:
                        clear();
                        function[0] = '\0';
                        flag2 = 0;
                        flag3 = 0;
                        
                        refresh();
                        break;
                }
                break;
        }
        print_menu(choice);
        if (function[0] != '\0') { // Check if function is not empty
            printw("f(x) = %s\n", function); // Print the function
            refresh();
        }
        if (flag2 == 1) {
            printw("f(%.2f) = %.2f\n", x, calculate_polynomial(function, x));
            refresh();
        }
        if (flag3 == 1) {
            printw("Tich phan cua f(x) tren [%.2f, %.2f] voi sai so khong qua %.2f la: %.4lf\n", a, b, e, integrate_trap(a, b, e, function));
            refresh();
        }
    }
}
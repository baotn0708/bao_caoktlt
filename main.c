#include <ncurses.h>
#include "xuly.h"
#include "tichphan.h"
#include "menu.h"

#define var_count 1
char function[100];
double x;
variable vars[] = {{"x", &x}};
double a, b, e;
double res_tichphan;
int flag2 = 0, flag3 = 0;

int main() {
    int row = 0, col = 0;  // Track both row and column of highlighted menu item
    int c;

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything
    keypad(stdscr, TRUE);

    print_menu(row, col);
    refresh();
    while (1) {
        c = getch(); // Use ncurses getch instead of getchar
        switch (c) {
            case KEY_UP: 
                if (row == 0)
                    row = 4;
                else
                    --row;
                break;
            case KEY_DOWN:
                if (!(row == 0 && col == 1)) {
                    if (row == 4)
                        row = 0;
                    else 
                        ++row;
                }
                break;
            case KEY_LEFT:
                if (col == 1)
                    --col;
                break;
            case KEY_RIGHT:
                if (col == 0 && row != 1 && row != 2 && row != 4)
                    ++col;
                break;
            case '\n':
                // Check if a handler exists for the selected option
                if (handlers[row][col] != NULL) {
                    // Call the handler function
                    handlers[row][col]();
                }
                break;
        }
        print_menu(row, col);
        if (function[0] != '\0') { // Check if function is not empty
            printw("f(x) = %s\n", function); // Print the function
            refresh();
        }
        if (flag2 == 1) {
            const char *expression = function;
            printw("f(%.2f) = %.2f\n", x, parse_expression(&expression, vars, var_count));
            refresh();
        }
        if (flag3 != 0) {
            if(flag3==1){
                printw("Tich phan cua f(x) tren [%.2f, %.2f] voi sai so khong qua %.2f theo pp hinh thang la: %.4lf\n", a, b, e, res_tichphan);
            }
            else{
                printw("Tich phan cua f(x) tren [%.2f, %.2f] voi sai so khong qua %.2f theo pp simpson la: %.4lf\n", a, b, e, res_tichphan);
            }
            refresh();
        }
    }
}

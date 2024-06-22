#ifndef MENU_H
#define MENU_H

#include "xuly.h"

extern char function[100];
extern double x;
extern variable vars[];
extern double a, b, e;
extern int precision;
extern double res_tichphan;
extern int flag2, flag3;
extern void (*handlers[5][2])();

void get_input_string(char* prompt, char* buffer, int buffer_size);
float get_input_float(char* prompt);
void handle_option_1();
void handle_option_2();
void handle_option_3();
void handle_option_6();
void exit_program();
void reset();
void print_menu(int highlight_row, int highlight_col);
void print_submenu_select_pp(int highlight);

#endif // MENU_H
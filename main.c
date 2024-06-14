#include <stdio.h>
#include <stdlib.h>
#include "xuly.h"
#include <unistd.h>
#include <termios.h>
#include "menu.h"
#include <fcntl.h>
#include <string.h>

char function[100];
float x;
void get_function() {
    printf("Nhap f(x): ");
    fgets(function, 100, stdin);
}
int main() {
    int choice = 1;
    int c;

    print_menu(choice);
    while (1) {
        if (kbhit()) {
            c = getchar();
            switch (c) {
                case 'A':
                    if (choice == 1)
                        choice = 5;
                    else
                        --choice;
                    break;
                case 'B':
                    if (choice == 5)
                        choice = 1;
                    else 
                        ++choice;
                    break;
                case '\n':
                    switch (choice) {
                        case 1:
                            get_function(); // call the new function when option 1 is chosen
                            sleep(1);
                            break;
                        case 2:
                            function[strcspn(function, "\n")] = 0;
                            if (function[0] != '\0'){
                                printf("Nhap diem can tinh: ");
                                scanf("%f", &x);
                                printf("%lf\n",calculate_polynomial(function, x));
                                sleep(1);
                                break;
                                // Call the function to calculate f(x) at x
                            }
                            else{
                                printf("Ban chua nhap ham so\n");
                                sleep(1);
                                break;
                            }
                        case 3:
                            if (function[0] != '\0'){
                                function[strcspn(function, "\n")] = 0;
                                printf("Nhap a: ");
                                float a;
                                scanf("%f", &a);
                                printf("Nhap b: ");
                                float b;
                                scanf("%f", &b);
                                printf("Nhap buoc nhay h:");
                                float h;
                                scanf("%f", &h);
                                print_polynomial_table(function, a, b, h);
                                sleep(1);
                                break;
                            }
                            else{
                                printf("Ban chua nhap ham so");
                                sleep(1);
                                break;
                            }
                        case 4:
                            if (function[0] != '\0'){
                                printf("Nhap a: ");
                                float a;
                                scanf("%f", &a);
                                printf("Nhap b: ");
                                float b;
                                scanf("%f", &b);
                                printf("Nhap sai so: ");
                                float e;
                                scanf("%f", &e);
                                // Call the function to calculate the integral of f(x) on the interval [a, b] with error e
                            }
                            else{
                                printf("Ban chua nhap ham so\n");
                                sleep(1);
                            }
                            sleep(1);
                            break;
                        case 5:
                            exit(0);
                            // break;
                    }
                    break;
            }
            print_menu(choice);
            if (function[0] != '\0') { // Check if function is not empty
                printf("f(x) = %s\n", function); // Print the function
            }
        }
    }

    return 0;
}

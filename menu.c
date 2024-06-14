#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define UP_ARROW 65
#define DOWN_ARROW 66
#define ENTER 10

char function[100]; // global variable to store the function

void print_menu(int highlight) {
    char *menu[] = {"Nhap f(x)", "Tinh f(x) tai 1 diem", "Lap bang gia tri tren mot doan(nhap hai dau mut tu ban phim)", "Tinh gan dung tich phan voi sai so cho truoc(mac dinh e<1e-4)", "Thoat chuong trinh"};
    int num_choices = sizeof(menu) / sizeof(char *);

    // Clear screen
    printf("\033[H\033[J");

    for (int i = 0; i < num_choices; i++) {
        if (highlight == i + 1) {
            printf("\033[7m%s\033[0m\n", menu[i]);
        } else {
            printf("%s\n", menu[i]);
        }
    }
}
int kbhit(void) { 
    struct termios oldt, newt; 
    int ch; 
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
    }
// New function to get the function from the user
void get_function() {
    printf("Nhap f(x): ");
    fgets(function, 100, stdin);
}

// ... rest of your code ...

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
                    printf("\n");
                    switch (choice) {
                        case 1:
                            get_function(); // call the new function when option 1 is chosen
                            sleep(1);
                            break;
                        // ... rest of your code ...
                    }
                    break;
            }
            print_menu(choice);
        }
    }

    return 0;
}
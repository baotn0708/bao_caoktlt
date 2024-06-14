#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "xuly.h"
#include <ctype.h>
#define MAX_SIZE 100

double calculate_polynomial(char *polynomial, double x0) {
    double result = 0.0;
    char *polynomial_copy = strdup(polynomial); // Tạo một bản sao của chuỗi đa thức để không sửa đổi chuỗi gốc
    char *ptr = polynomial_copy;

    while (*ptr) {
        int coefficient = 1; // Mặc định hệ số là 1
        int exponent = 0; // Mặc định số mũ là 0
        int sign = 1; // Mặc định dấu là dương

        // Xác định dấu của hạng tử
        if (*ptr == '+') {
            sign = 1;
            ptr++;
        } else if (*ptr == '-') {
            sign = -1;
            ptr++;
        }

        // Kiểm tra hệ số và số mũ
        if (isdigit(*ptr)) {
            sscanf(ptr, "%d", &coefficient);
            while (isdigit(*ptr)) ptr++; // Bỏ qua các chữ số của hệ số
        }
        if (*ptr == 'x') {
            ptr++;
            if (*ptr == '^') {
                ptr++;
                sscanf(ptr, "%d", &exponent);
                while (isdigit(*ptr)) ptr++; // Bỏ qua các chữ số của số mũ
            } else {
                exponent = 1;
            }
        }

        // Cập nhật hệ số với dấu
        coefficient *= sign;

        // Tính giá trị của hạng tử và cộng vào kết quả
        result += coefficient * pow(x0, exponent);

        // Tìm hạng tử tiếp theo
        while (*ptr && *ptr != '+' && *ptr != '-') {
            ptr++;
        }
    }

    free(polynomial_copy);
    return result;
}


void print_polynomial_table(char *polynomial, double a, double b, double h) {
    // Print the header of the table
    printf("%-7s","x: ");
    for (double i = a; i <= b + h/2; i += h) {
        printf("%6.2lf", i); // Print the value of x with a fixed width of 6 characters
    }
    printf("\n");

    printf("%-7s","f(x): ");
    for (double i = a; i <= b + h/2; i += h) {
        double result = calculate_polynomial(polynomial, i);
        printf("%6.2lf", result); // Print the value of f(x) with a fixed width of 6 characters
    }
    printf("\n");
}

// int main() {
//     char polynomial[MAX_SIZE];
//     double x0, a, b, h;

//     printf("Enter a polynomial: ");
//     fgets(polynomial, MAX_SIZE, stdin);
//     polynomial[strcspn(polynomial, "\n")] = 0;  // remove trailing newline

//     // printf("Enter the value of x0: ");
//     // scanf("%lf", &x0);

//     printf("Enter the lower limit (a): ");
//     scanf("%lf", &a);

//     printf("Enter the upper limit (b): ");
//     scanf("%lf", &b);

//     printf("Enter the step size (h): ");
//     scanf("%lf", &h);

//     print_polynomial_table(polynomial, a, b, h); // Print the table

//     return 0;
// }
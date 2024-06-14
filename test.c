#include<stdio.h>
#include<stdlib.h>
#include "xuly.h"
#include<string.h>
#define MAX_SIZE 100

int main() {
    char polynomial[MAX_SIZE];
    double x0, a, b, h;

    printf("Enter a polynomial: ");
    fgets(polynomial, MAX_SIZE, stdin);
    polynomial[strcspn(polynomial, "\n")] = 0;  // remove trailing newline

    printf("Enter the value of x0: ");
    scanf("%lf", &x0);
    printf("%lf", calculate_polynomial(polynomial, x0));

    // printf("Enter the lower limit (a): ");
    // scanf("%lf", &a);

    // printf("Enter the upper limit (b): ");
    // scanf("%lf", &b);

    // printf("Enter the step size (h): ");
    // scanf("%lf", &h);

    // print_polynomial_table(polynomial, a, b, h);

    return 0;
}
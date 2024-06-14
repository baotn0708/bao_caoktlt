#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

double calculate_polynomial(char *polynomial, double x0) {
    double result = 0.0;
    char *token = strtok(polynomial, "+");
    while (token != NULL) {
        int coefficient = 1;
        int exponent = 0;
        if (strchr(token, 'x') != NULL) {
            if (sscanf(token, "%dx^%d", &coefficient, &exponent) != 2) {
                sscanf(token, "x^%d", &exponent);
            }
        } else {
            sscanf(token, "%d", &coefficient);
        }
        result += coefficient * pow(x0, exponent);
        token = strtok(NULL, "+");
    }
    return result;
}

int main() {
    char polynomial[MAX_SIZE];
    double x0;

    printf("Enter a polynomial: ");
    fgets(polynomial, MAX_SIZE, stdin);
    polynomial[strcspn(polynomial, "\n")] = 0;  // remove trailing newline

    printf("Enter the value of x0: ");
    scanf("%lf", &x0);

    double result = calculate_polynomial(polynomial, x0);
    printf("The value of the polynomial at x0 is: %.2lf\n", result);

    return 0;
}
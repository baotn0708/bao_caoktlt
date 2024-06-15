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
double trapezoidal_rule(double a, double b, double *x_values, double *y_values, int n) {
    double h = (b - a) / n;
    double s = y_values[0] + y_values[n];

    for (int i = 1; i < n; i++) {
        s += 2 * y_values[i];
    }

    return (h / 2) * s;
}
double simpson_rule(double a, double b, double *x_values, double *y_values, int n) {
    double h = (b - a) / n;
    double s = y_values[0] + y_values[n];

    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            s += 2 * y_values[i];
        } else {
            s += 4 * y_values[i];
        }
    }

    return (h / 3) * s;
}
double integrate_trap(double a, double b, double epsilon, char* poly){
    int num_points = 3;  // number of points
    double *x_values = malloc(num_points * sizeof(double));
    double *y_values = malloc(num_points * sizeof(double));
    
    double step = (b - a) / (num_points - 1);  // calculate the step size
    
    for (int i = 0; i < num_points; i++) {
        x_values[i] = a + i * step;  // calculate the x values
        y_values[i] = calculate_polynomial(poly ,x_values[i]);  // calculate the y values
    }
    
    double result=-1, old_result;
    do{
        old_result = result;
        x_values = realloc(x_values, num_points * sizeof(double));
        y_values = realloc(y_values, num_points * sizeof(double));
        step = (b - a) / (num_points - 1);  // calculate the step size
        for (int i = 0; i < num_points; i++) {
            x_values[i] = a + i * step;  // calculate the x values
            y_values[i] = calculate_polynomial(poly ,x_values[i]);  // calculate the y values
        }
        result = trapezoidal_rule(a, b, x_values, y_values, num_points);
        num_points *= 2;
    }while (fabs(result - old_result) > epsilon);
    print_polynomial_table(poly, a, b, (b-a)/(num_points-1) );
    free(x_values);
    free(y_values);

    return result;

}
double integrate_simp(double a, double b, double epsilon, char* function){
    int num_points = 3;  // number of points
    double *x_values = malloc(num_points * sizeof(double));
    double *y_values = malloc(num_points * sizeof(double));
    
    double step = (b - a) / (num_points - 1);  // calculate the step size
    
    for (int i = 0; i < num_points; i++) {
        x_values[i] = a + i * step;  // calculate the x values
        y_values[i] = calculate_polynomial(function ,x_values[i]);  // calculate the y values
    }
    
    double result=-1, old_result;
    do{
        old_result = result;
        x_values = realloc(x_values, num_points * sizeof(double));
        y_values = realloc(y_values, num_points * sizeof(double));
        step = (b - a) / (num_points - 1);  // calculate the step size
        for (int i = 0; i < num_points; i++) {
            x_values[i] = a + i * step;  // calculate the x values
            y_values[i] = calculate_polynomial(function ,x_values[i]);  // calculate the y values
        }
        result = simpson_rule(a, b, x_values, y_values, num_points);
        num_points *= 2;
    }while (fabs(result - old_result) > epsilon);

    free(x_values);
    free(y_values);

    return result;
}
// int main() {
//     char polynomial[MAX_SIZE];
//     double a, b, epsilon;

//     printf("Enter a polynomial: ");
//     fgets(polynomial, MAX_SIZE, stdin);
//     polynomial[strcspn(polynomial, "\n")] = 0;  // remove trailing newline

//     // printf("Enter the value of x0: ");
//     // scanf("%lf", &x0);

//     printf("Enter the lower limit (a): ");
//     scanf("%lf", &a);

//     printf("Enter the upper limit (b): ");
//     scanf("%lf", &b);
//     printf("Enter epsilon:");
//     scanf("%lf", &epsilon);

//     printf("Integrate poly [%6.2lf, %6.2lf]: %6.2lf", a, b, integrate(a, b, epsilon, polynomial));

//     return 0;
// }
// double integrate_trap(double (*f)(double), double a, double b, double epsilon) {
//     int num_points = 3;  // number of points
//     double *x_values = malloc(num_points * sizeof(double));
//     double *y_values = malloc(num_points * sizeof(double));
    
//     double step = (b - a) / (num_points - 1);  // calculate the step size
    
//     for (int i = 0; i < num_points; i++) {
//         x_values[i] = a + i * step;  // calculate the x values
//         y_values[i] = f(x_values[i]);  // calculate the y values
//     }
    
//     double result=-1, old_result;
//     do{
//         old_result = result;
//         x_values = realloc(x_values, num_points * sizeof(double));
//         y_values = realloc(y_values, num_points * sizeof(double));
//         step = (b - a) / (num_points - 1);  // calculate the step size
//         for (int i = 0; i < num_points; i++) {
//             x_values[i] = a + i * step;  // calculate the x values
//             y_values[i] = f(x_values[i]);  // calculate the y values
//         }
//         result = trapezoidal_rule(a, b, x_values, y_values, num_points);
//         num_points *= 2;
//     }while (fabs(result - old_result) > epsilon);

//     free(x_values);
//     free(y_values);

//     return result;
// }
// double integrate_simp(double (*f)(double), double a, double b, double epsilon) {
//     int num_points = 3;  // number of points
//     double *x_values = malloc(num_points * sizeof(double));
//     double *y_values = malloc(num_points * sizeof(double));
    
//     double step = (b - a) / (num_points - 1);  // calculate the step size
    
//     for (int i = 0; i < num_points; i++) {
//         x_values[i] = a + i * step;  // calculate the x values
//         y_values[i] = f(x_values[i]);  // calculate the y values
//     }
    
//     double result=-1, old_result;
//     do{
//         old_result = result;
//         x_values = realloc(x_values, num_points * sizeof(double));
//         y_values = realloc(y_values, num_points * sizeof(double));
//         step = (b - a) / (num_points - 1);  // calculate the step size
//         for (int i = 0; i < num_points; i++) {
//             x_values[i] = a + i * step;  // calculate the x values
//             y_values[i] = f(x_values[i]);  // calculate the y values
//         }
//         result = simpson_rule(a, b, x_values, y_values, num_points);
//         num_points *= 2;
//     }while (fabs(result - old_result) > epsilon);

//     free(x_values);
//     free(y_values);

//     return result;
// }
// double f(double x){
//     return x*x;
// }

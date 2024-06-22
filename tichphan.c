#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "xuly.h"
#include <string.h>
#include "phu.h"

#define var_count 1



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

double integrate(double a, double b, double epsilon, const char* func, int flag, int precision) {
    int num_points = 3;  // số điểm ban đầu
    double *x_values = malloc(num_points * sizeof(double));
    double *y_values = malloc(num_points * sizeof(double));
    
    double step = (b - a) / (num_points - 1);  // tính kích thước bước
    
    double x0 = 0;
    variable vars[] = {{"x", &x0}};
    
    for (int i = 0; i < num_points; i++) {
        x_values[i] = a + i * step;  // tính các giá trị x
        x0 = x_values[i];
        const char* func_copy = func;
        y_values[i] = parse_expression(&func_copy, vars, var_count);  // tính các giá trị y
    }
    
    char log_message[100];
    sprintf(log_message, "Lan thu %d:", (int)floor((log(2*num_points/3)/log(2))));
    write_log(log_message);
    print_table(x_values, y_values, num_points);
    double result = (flag == 1) ? trapezoidal_rule(a, b, x_values, y_values, num_points) : simpson_rule(a, b, x_values, y_values, num_points);
    double old_result;
    do {
        old_result = result;
        num_points *= 2;
        x_values = realloc(x_values, num_points * sizeof(double));
        y_values = realloc(y_values, num_points * sizeof(double));
        step = (b - a) / (num_points - 1);  // tính lại kích thước bước
        for (int i = 0; i < num_points; i++) {
            x_values[i] = a + i * step;  // tính các giá trị x
            x0 = x_values[i];
            const char* func_copy = func;
            y_values[i] = parse_expression(&func_copy, vars, var_count);  // tính các giá trị y
        }
        sprintf(log_message, "Lan thu %d:", (int)floor((log(2*num_points/3)/log(2))));
        write_log(log_message);
        print_table(x_values, y_values, num_points);
        result = (flag == 1) ? trapezoidal_rule(a, b, x_values, y_values, num_points) : simpson_rule(a, b, x_values, y_values, num_points);
    } while (fabs(result - old_result) > epsilon);
    if(flag == 1){
        sprintf(log_message, "Tich phan cua f(x) tren [%.2lf, %.2lf] theo phuong phap hinh thang la: %.*lf", a, b, precision, result);
    } else {
        sprintf(log_message, "Tich phan cua f(x) tren [%.2lf, %.2lf] theo phuong phap Simpson la: %.*lf", a, b, precision, result);
    }
    write_log(log_message);
    free(x_values);
    free(y_values);
    return result;
}
// double integrate_simp(double a, double b, double epsilon, const char* func) {
//     int num_points = 3;  // số điểm ban đầu
//     double *x_values = malloc(num_points * sizeof(double));
//     double *y_values = malloc(num_points * sizeof(double));
    
//     double step = (b - a) / (num_points - 1);  // tính kích thước bước
    
//     double x0 = 0;
//     variable vars[] = {{"x", &x0}};
    
//     for (int i = 0; i < num_points; i++) {
//         x_values[i] = a + i * step;  // tính các giá trị x
//         x0 = x_values[i];
//         const char* func_copy = func;
//         y_values[i] = parse_expression(&func_copy, vars, var_count);  // tính các giá trị y
//     }
    
//     char log_message[100];
//     // sprintf(log_message, "Lan thu %d:", (int)floor((log(2*num_points/3)/log(2))));
//     // write_log(log_message);
//     // print_table(x_values, y_values, num_points);
//     double result = simpson_rule(a, b, x_values, y_values, num_points);
//     double old_result;
//     do {
//         old_result = result;
//         num_points *= 2;
//         x_values = realloc(x_values, num_points * sizeof(double));
//         y_values = realloc(y_values, num_points * sizeof(double));
//         step = (b - a) / (num_points - 1);  // tính lại kích thước bước
//         for (int i = 0; i < num_points; i++) {
//             x_values[i] = a + i * step;  // tính các giá trị x
//             x0 = x_values[i];
//             const char* func_copy = func;
//             y_values[i] = parse_expression(&func_copy, vars, var_count);  // tính các giá trị y
//         }
//         // sprintf(log_message, "Lan thu %d:", (int)floor((log(2*num_points/3)/log(2))));
//         // write_log(log_message);
//         // print_table(x_values, y_values, num_points);
//         result = simpson_rule(a, b, x_values, y_values, num_points);
//     } while (fabs(result - old_result) > epsilon);
//     // sprintf(log_message, "Tich phan cua f(x) tren [%.2lf, %.2lf] theo phuong phap Simpson la: %.4lf", a, b, result);
//     // write_log(log_message);

//     free(x_values);
//     free(y_values);
    
//     return result;
// }


// int main()
// {
//     char expr[100];
//     double a, b, e;

//     // Nhập giá trị a, b, epsilon từ bàn phím
//     printf("Nhập giá trị a: ");
//     scanf("%lf", &a);
//     printf("Nhập giá trị b: ");
//     scanf("%lf", &b);
//     printf("Nhập giá trị epsilon: ");
//     scanf("%lf", &e);

//     // Nhập biểu thức hàm từ bàn phím
//     printf("Nhập biểu thức hàm f(x): ");
//     scanf("%s", expr);
//     const char *expression = expr;

//     double result = integrate_simp(a, b, e, expression);

//     printf("Tích phân của f(x) trên [%f, %f] là: %lf\n", a, b, result);

//     return 0;
// }
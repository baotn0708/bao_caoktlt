#include <stdio.h>
#include<math.h>
#include<stdlib.h>
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
double f(double x ){
    return x*x;
}

double integrate_trap(double (*f)(double), double a, double b, double epsilon) {
    int num_points = 3;  // number of points
    double *x_values = malloc(num_points * sizeof(double));
    double *y_values = malloc(num_points * sizeof(double));
    
    double step = (b - a) / (num_points - 1);  // calculate the step size
    
    for (int i = 0; i < num_points; i++) {
        x_values[i] = a + i * step;  // calculate the x values
        y_values[i] = f(x_values[i]);  // calculate the y values
    }
    
    double result=-1, old_result;
    do{
        old_result = result;
        x_values = realloc(x_values, num_points * sizeof(double));
        y_values = realloc(y_values, num_points * sizeof(double));
        step = (b - a) / (num_points - 1);  // calculate the step size
        for (int i = 0; i < num_points; i++) {
            x_values[i] = a + i * step;  // calculate the x values
            y_values[i] = f(x_values[i]);  // calculate the y values
        }
        result = trapezoidal_rule(a, b, x_values, y_values, num_points);
        num_points *= 2;
    }while (fabs(result - old_result) > epsilon);

    free(x_values);
    free(y_values);

    return result;
}
double integrate_simp(double (*f)(double), double a, double b, double epsilon) {
    int num_points = 3;  // number of points
    double *x_values = malloc(num_points * sizeof(double));
    double *y_values = malloc(num_points * sizeof(double));
    
    double step = (b - a) / (num_points - 1);  // calculate the step size
    
    for (int i = 0; i < num_points; i++) {
        x_values[i] = a + i * step;  // calculate the x values
        y_values[i] = f(x_values[i]);  // calculate the y values
    }
    
    double result=-1, old_result;
    do{
        old_result = result;
        x_values = realloc(x_values, num_points * sizeof(double));
        y_values = realloc(y_values, num_points * sizeof(double));
        step = (b - a) / (num_points - 1);  // calculate the step size
        for (int i = 0; i < num_points; i++) {
            x_values[i] = a + i * step;  // calculate the x values
            y_values[i] = f(x_values[i]);  // calculate the y values
        }
        result = simpson_rule(a, b, x_values, y_values, num_points);
        num_points *= 2;
    }while (fabs(result - old_result) > epsilon);

    free(x_values);
    free(y_values);

    return result;
}

// int main() {
//     double a = 0;  // start value
//     double b = 1;  // end value
//     double epsilon = .01;  // epsilon value
//     printf("Tích phân gần đúng của hàm f(x) trên đoạn [%.2lf, %.2lf] là: %.2lf\n", a, b, integrate(f, a, b, epsilon));
//     // printf("%lf\n", y_values[(num_points-1)/2]);
//     // result = simpson_rule(a, b, x_values, y_values, (num_points-1)/2);
//     // printf("Tích phân gần đúng của hàm f(x) trên đoạn [%.2lf, %.2lf] là: %.2lf\n", a, b, result);
//     // free(x_values);
//     // free(y_values);
//     return 0;
// }
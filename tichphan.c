#include <stdio.h>

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
int main() {
    double x_values[] = {0,1/4,1/2,3/4, 1};
    double y_values[] = { 0, 0.0625, 0.25, 0.5625, 1};
    int n = sizeof(x_values) / sizeof(x_values[0]);
    double a = x_values[0];  // xo
    double b = x_values[n-1];  // xn
    n--;
    double result = trapezoidal_rule(a, b, x_values, y_values, n);
    printf("Tích phân gần đúng của hàm f(x) trên đoạn [%.2lf, %.2lf] là: %.2lf\n", a, b, result);
    result = simpson_rule(a, b, x_values, y_values, n);
    printf("Tích phân gần đúng của hàm f(x) trên đoạn [%.2lf, %.2lf] là: %.2lf\n", a, b, result);

    return 0;
}
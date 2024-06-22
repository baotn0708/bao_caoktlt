#ifndef TICHPHAN_H
#define TICHPHAN_H


void print_table(double *x_values, double *y_values, int n);
double trapezoidal_rule(double a, double b, double *x_values, double *y_values, int n);
double simpson_rule(double a, double b, double *x_values, double *y_values, int n);
double integrate(double a, double b, double epsilon, const char* func, int flag, int precision);


#endif // XULY_H
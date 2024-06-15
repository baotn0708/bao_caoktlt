#ifndef XULY_H
#define XULY_H

double calculate_polynomial(char *polynomial, double x0);
void print_polynomial_table(char *polynomial, double a, double b, double h);
double trapezoidal_rule(double a, double b, double *x_values, double *y_values, int n);
double simpson_rule(double a, double b, double *x_values, double *y_values, int n);
double integrate_trap(double a, double b, double epsilon, char* function);
double integrate_simp(double a, double b, double epsilon, char* function);
#endif // XULY_H
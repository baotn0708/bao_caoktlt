#ifndef TICHPHAN_H
#define TICHPHAN_H

double trapezoidal_rule(double a, double b, double *x_values, double *y_values, int n);
double simpson_rule(double a, double b, double *x_values, double *y_values, int n);
double integrate_trap(double a, double b, double epsilon, const char* func);
double integrate_simp(double a, double b, double epsilon, const char* func);


#endif // XULY_H
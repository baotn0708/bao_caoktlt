#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *name;
    double *address;
} variable;

double parse_expression(const char **expression, variable *vars, int var_count);
double parse_term(const char **expression, variable *vars, int var_count);
double parse_factor(const char **expression, variable *vars, int var_count);
double parse_primary(const char **expression, variable *vars, int var_count);
double evaluate_function(const char *name, double arg);
double evaluate_variable(const char *name, variable *vars, int var_count);

double parse_expression(const char **expression, variable *vars, int var_count) {
    double result = parse_term(expression, vars, var_count);
    while (**expression == '+' || **expression == '-') {
        char op = **expression;
        (*expression)++;
        double term = parse_term(expression, vars, var_count);
        if (op == '+') result += term;
        else result -= term;
    }
    return result;
}

double parse_term(const char **expression, variable *vars, int var_count) {
    double result = parse_factor(expression, vars, var_count);
    while (**expression == '*' || **expression == '/') {
        char op = **expression;
        (*expression)++;
        double factor = parse_factor(expression, vars, var_count);
        if (op == '*') result *= factor;
        else result /= factor;
    }
    return result;
}

double parse_factor(const char **expression, variable *vars, int var_count) {
    double result = parse_primary(expression, vars, var_count);
    while (**expression == '^') {
        (*expression)++;
        double exponent = parse_primary(expression, vars, var_count);
        result = pow(result, exponent);
    }
    return result;
}

double parse_primary(const char **expression, variable *vars, int var_count) {
    double result;
    if (**expression == '(') {
        (*expression)++;
        result = parse_expression(expression, vars, var_count);
        if (**expression == ')') (*expression)++;
    } else if (isalpha(**expression)) {
        const char *start = *expression;
        while (isalnum(**expression)) (*expression)++;
        char name[100];
        strncpy(name, start, *expression - start);
        name[*expression - start] = '\0';
        if (**expression == '(') {
            (*expression)++;
            double arg = parse_expression(expression, vars, var_count);
            if (**expression == ')') (*expression)++;
            result = evaluate_function(name, arg);
        } else {
            result = evaluate_variable(name, vars, var_count);
        }
    } else {
        char *end;
        result = strtod(*expression, &end);
        *expression = end;
    }
    return result;
}

double evaluate_function(const char *name, double arg) {
    if (strcmp(name, "sin") == 0) return sin(arg);
    if (strcmp(name, "cos") == 0) return cos(arg);
    if (strcmp(name, "tan") == 0) return tan(arg);
    if (strcmp(name, "log") == 0) return log(arg);
    if (strcmp(name, "exp") == 0) return exp(arg);
    if (strcmp(name, "sqrt") == 0) return sqrt(arg);
    return 0.0; // Hàm không xác định
}

double evaluate_variable(const char *name, variable *vars, int var_count) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(name, vars[i].name) == 0) {
            return *(vars[i].address);
        }
    }
    return 0.0; // Biến không xác định
}

int main() {
    char expr[100];
    double x0;

    // Nhập giá trị x0 từ bàn phím
    printf("Nhập giá trị x0: ");
    scanf("%lf", &x0);

    // Nhập biểu thức hàm từ bàn phím
    printf("Nhập biểu thức hàm f(x): ");
    scanf("%s", expr);

    variable vars[] = {{"x", &x0}};
    const char *expression = expr;
    double result = parse_expression(&expression, vars, 1);

    printf("f(%lf) = %lf\n", x0, result);

    return 0;
}

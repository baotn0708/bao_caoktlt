#ifndef XULY_H
#define XULY_H

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
void write_log(const char* message);

#endif // XULY_H
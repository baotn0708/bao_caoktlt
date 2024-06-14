#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

        // Kiểm tra hệ số (nếu có)
        if (isdigit(*ptr) || (*ptr == 'x')) {
            if (sscanf(ptr, "%dx^%d", &coefficient, &exponent) == 2) {
                // Cả hệ số và số mũ đã được gán giá trị đúng
            } else if (sscanf(ptr, "%dx", &coefficient) == 1) {
                exponent = 1;
            } else if (sscanf(ptr, "x^%d", &exponent) == 1) {
                coefficient = 1;
            } else if (sscanf(ptr, "%d", &coefficient) == 1) {
                exponent = 0;
            } else if (*ptr == 'x') {
                coefficient = 1;
                exponent = 1;
            }

            // Cập nhật hệ số với dấu
            coefficient *= sign;
        }

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

int main() {
    char polynomial[] = "x^3+x^2+1";
    double x0 = 2.0;
    double result = calculate_polynomial(polynomial, x0);
    printf("Giá trị của đa thức tại x = %.2f là: %.2f\n", x0, result);
    return 0;
}

#include <stdio.h>
#include <string.h>

void write_log(const char* message) {
    FILE* file = fopen("log.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", message);
        fclose(file);
    }
}
void print_table(double *x_values, double *y_values, int n) {
    char log_message[1000] = "";  // tạo chuỗi log_message với kích thước đủ lớn

    strcat(log_message, "x: ");
    for (int i = 0; i < n; i++) {
        if (i < 3 || i >= n - 3) {
            char temp[50];
            sprintf(temp, "%10.2f\t", x_values[i]);
            strcat(log_message, temp);
        } else if (i == 3) {
            strcat(log_message, "...\t");
        }
    }
    strcat(log_message, "\n");

    strcat(log_message, "y: ");
    for (int i = 0; i < n; i++) {
        if (i < 3 || i >= n - 3) {
            char temp[50];
            sprintf(temp, "%10.2f\t", y_values[i]);
            strcat(log_message, temp);
        } else if (i == 3) {
            strcat(log_message, "...\t");
        }
    }
    strcat(log_message, "\n");

    write_log(log_message);  // ghi log_message vào file log
}
void remove_spaces(char* s) {
    char* d = s; // Con trỏ đích để sao chép ký tự không phải khoảng trắng
    do {
        while (*s == ' ') { // Bỏ qua khoảng trắng
            s++;
        }
    } while ((*d++ = *s++)); // Sao chép ký tự không phải khoảng trắng và tăng con trỏ
}
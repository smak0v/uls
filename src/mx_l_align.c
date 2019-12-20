#include "uls.h"

char *mx_l_align(char *str, int spaces_count) {
    int len = mx_strlen(str) + spaces_count;
    char *new_str = mx_strnew(len);

    for (int j = 0; j < mx_strlen(str); j++)
        new_str[j] = str[j];
    for (int i = mx_strlen(str); i < mx_strlen(str) + spaces_count; i++)
        new_str[i] = ' ';
    mx_strdel(&str);
    return new_str;
}

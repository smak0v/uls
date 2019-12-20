#include "uls.h"

char *mx_r_align(char *str, int spaces_count) {
    int len = mx_strlen(str) + spaces_count;
    char *new_str = mx_strnew(len);

    for (int i = 0; i < spaces_count; i++)
        new_str[i] = ' ';
    for (int j = 0, i = spaces_count; j < mx_strlen(str); j++, i++)
        new_str[i] = str[j];
    mx_strdel(&str);
    return new_str;
}

#include "uls.h"

void mx_get_formatted_size(int int_part, int float_part, char **res) {
    char *res_copy = NULL;
    char *tmp = NULL;

    if (mx_numlen(int_part) > 1)
        *res = mx_strnew(mx_numlen(int_part) + 1);
    else
        *res = mx_strnew(mx_numlen(int_part) + mx_numlen(float_part) + 1);
    res_copy = *res;
    tmp = mx_itoa(int_part);
    res_copy = mx_strcpy(res_copy, tmp);
    mx_strdel(&tmp);
    res_copy += mx_numlen(int_part);
    if (mx_numlen(int_part) < 2) {
        res_copy = mx_strcpy(res_copy, ".");
        res_copy += 1;
        tmp = mx_itoa(float_part);
        res_copy = mx_strcpy(res_copy, tmp);
        mx_strdel(&tmp);
    }
}

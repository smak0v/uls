#include "uls.h"

static char *convert_float(float number);
static char *get_result(char sizes, char *number);

char *mx_convert_size(long long size) {
    long long mult = 1024LL * 1024LL * 1024LL * 1024LL * 1024LL;
    char *sizes[] = {"P", "T", "G", "M", "K", "B"};
    char *result = NULL;

    if (size == 0)
        return mx_strdup("0");
    for (int i = 0; i < 6; i++, mult /= 1024) {
        if (size < mult)
            continue;
        if (size % mult == 0)
            result = get_result(*sizes[i], mx_itoa(size / mult));
        else
            result = get_result(*sizes[i], convert_float((float)size / mult));
        return result;
    }
    return result;
}

static char *convert_float(float number) {
    int int_part = (int)number;
    char *int_res = NULL;
    float float_part = 0;
    char *result = NULL;
    char *tmp = NULL;

    if (mx_numlen(int_part) > 1)
        return mx_itoa(int_part);
    int_res = mx_itoa(int_part);
    float_part = number - (float)int_part;
    float_part = float_part * mx_pow(10, 1);
    result = mx_strnew(mx_strlen(int_res) + 2);
    result = mx_strcpy(result, int_res);
    result[mx_strlen(result)] = '.';
    tmp = mx_itoa((int)float_part);
    result[mx_strlen(result)] = tmp[0];
    mx_strdel(&tmp);
    mx_strdel(&int_res);
    return result;
}

static char *get_result(char size, char *number) {
    char *result = NULL;

    result = mx_strnew(mx_strlen(number) + 1);
    result = mx_strcpy(result, number);
    result[mx_strlen(result)] = size;
    mx_strdel(&number);
    return result;
}

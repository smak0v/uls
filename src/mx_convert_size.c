#include "uls.h"

static char *to_float(float number);
// static void format_int_part(int *int_part, int *int_float_part);
static void format_float_part(int *int_float_part);
static char *get_result(char size, char *number);

char *mx_convert_size(uint64_t size) {
    uint64_t mult = 1024LL * 1024LL * 1024LL * 1024LL * 1024LL;
    char *sizes[] = {"P", "T", "G", "M", "K", "B"};
    char *result = NULL;

    if (size == 0)
        return mx_strdup("0");
    for (int i = 0; i < 6; i++, mult /= 1024) {
        if (size < mult)
            continue;
        if (size % mult == 0) {
            if (*sizes[i] != 'B')
                result = get_result(*sizes[i], to_float((float)size / mult));
            else
                result = get_result(*sizes[i], mx_itoa(size / mult));
        }
        else
            result = get_result(*sizes[i], to_float((float)size / mult));
        return result;
    }
    return result;
}

static char *to_float(float number) {
    int int_part = (int)number;
    float float_part = (number - (float)int_part) * mx_pow(10, 2);
    int int_float_part = (int)float_part;
    char *res = NULL;

    format_float_part(&int_float_part);
    //format_int_part(&int_part, &int_float_part);
    mx_get_formatted_size(int_part, int_float_part, &res);
    return res;
}

// static void format_int_part(int *int_part, int *int_float_part) {
//     char *str_float_part = mx_itoa(*int_float_part);

//     if (mx_numlen(*int_float_part) == 1)
//         *int_float_part = 0;
//     else if (str_float_part[0] > '5' && str_float_part[0] <= '9') {
//         *int_float_part = 0;
//         *int_part += 1;
//     }
//     mx_strdel(&str_float_part);
// }

static void format_float_part(int *int_float_part) {
    char *str_float_part = NULL;

    if (*int_float_part == 0)
        return;
    if (mx_numlen(*int_float_part) == 1) {
        if (*int_float_part >= 5 && *int_float_part <= 9) {
            *int_float_part = 1;
            return;
        }
        return;
    }
    str_float_part = mx_itoa(*int_float_part);
    if (str_float_part[1] >= '5' && str_float_part[1] <= '8') {
        *int_float_part = (str_float_part[0] + 1) - '0';
        mx_strdel(&str_float_part);
    }
    else if (str_float_part[0] == '9') {

    }
    else {
        *int_float_part = str_float_part[0] - '0';
        mx_strdel(&str_float_part);
    }
}

static char *get_result(char size, char *number) {
    char *result = mx_strnew(mx_strlen(number) + 1);

    if (number) {
        result = mx_strcpy(result, number);
        result[mx_strlen(result)] = size;
        mx_strdel(&number);
    }
    return result;
}

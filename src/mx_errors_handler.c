#include "uls.h"

void mx_errors_handler(char **flags, char **files) {
    char *error_flag = mx_check_flags(flags);

    if (error_flag) {
        mx_print_error(ILLEGAL_OPTION);
        mx_print_error_endl(error_flag);
        mx_print_error(USAGE_ERROR);
        mx_del_strarr(&flags);
        mx_del_strarr(&files);
        exit(-1);
    }
}

#include "uls.h"

void mx_check_usage_error(char **flags, char **files) {
    char *error_flag = mx_check_flags(flags);

    if (error_flag) {
        mx_print_error("uls: illegal option -- ");
        mx_print_error_endl(error_flag);
        mx_print_error("usage: uls [-");
        mx_print_error(ALLOWED_FLAGS);
        mx_print_error_endl("] [file ...]");
        mx_del_strarr(&flags);
        mx_del_strarr(&files);
        exit(1);
    }
}

void mx_print_uls_error(char *filename, char *error) {

    mx_print_error("uls: ");
    mx_print_error(filename);
    mx_print_error(": ");
    mx_print_error_endl(error);
}

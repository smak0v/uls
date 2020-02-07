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

void mx_print_not_found(t_list **err_list) {
    t_list *node = NULL;

    if (err_list && *err_list) {
        mx_sort_errors(err_list);
        node = *err_list;
        while (node) {
            mx_print_error("uls: ");
            mx_print_error(node->data);
            mx_print_error(": No such file or directory\n");
            node = node->next;
        }
        mx_clear_list(err_list);
    }
}

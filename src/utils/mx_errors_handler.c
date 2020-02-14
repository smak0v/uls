#include "uls.h"

void mx_check_usage_error(char **flags, char **files) {
    char *error_flag = mx_check_flag(flags);

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

static void permission_denied(t_list **errors) {
    t_list *tmp = *errors;

    while (tmp) {
        mx_print_error(tmp->data);
        mx_print_error(":\nuls: ");
        mx_print_error((char *)mx_memrchr(tmp->data, '/',
                       mx_strlen(tmp->data)) + 1);
        mx_print_error(": Permission denied\n");
        tmp = tmp->next;
    }
    mx_clear_list(errors);
}

void mx_print_uls_error(t_list *err_list) {
    t_list *node = err_list;
    t_list *tmp = NULL;

    while (node) {
        t_error *error = node->data;

        if (error->error == 13) {
            mx_push_back(&tmp, mx_strdup(error->filename));
            node = node->next;
            continue;
        }
        mx_print_error("uls: ");
        mx_print_error(error->filename);
        mx_print_error(": ");
        mx_print_error_endl(strerror(error->error));
        node = node->next;
    }
    if (tmp)
        permission_denied(&tmp);
    mx_clear_err_list(&err_list);
}

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

static void permission_denied(t_list **errors) {
    t_list *tp = *errors;

    while (tp) {
        mx_print_error(tp->data);
        mx_print_error(":\nuls: ");
        mx_print_error((char *)mx_memrchr(tp->data, '/', mx_strlen(tp->data)) + 1);
        mx_print_error(": Permission denied\n");
        tp = tp->next;
    }

    mx_clear_list(errors);
}

void mx_print_uls_error(t_list *err_list) {
    t_list *node = err_list;
    t_list *tmp = NULL;

    while (node) {
        t_error *error = node->data;
        if (error->error == 13) {
            mx_push_back(&tmp, error->filename);
            node = node->next;
            continue ;
        }
        mx_print_error("uls: ");
        mx_print_error(error->filename);
        mx_print_error(": ");
        mx_print_error_endl(strerror(error->error));
        node = node->next;
    }

    if (tmp)
        permission_denied(&tmp);
}

void mx_print_notfound(t_list *err_list) {
    t_list *node = err_list;

    while (node) {
        mx_print_error("uls: ");
        mx_print_error(node->data);
        mx_print_error(": No such file or directory");
        node = node->next;
    }
}

#include "libmx.h"

void mx_print_error(const char *error) {
    write(2, error, mx_strlen(error));
}

void mx_print_not_found(t_list *err_list) {
    t_list *node = err_list;

    while (node) {
        mx_print_error("uls: ");
        mx_print_error(node->data);
        mx_print_error(": No such file or directory\n");
        node = node->next;
    }
}

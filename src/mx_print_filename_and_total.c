#include "uls.h"

void mx_print_filename_and_total(t_list *node, t_list *inner_node) {
    mx_printstr(((t_list *)node->data)->data);
    mx_printstr(":\n");
    if (mx_list_size(inner_node))
        mx_print_total(inner_node);
}

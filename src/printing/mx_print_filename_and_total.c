#include "uls.h"

void mx_print_filename_and_total(t_list *node, t_list *inner_node,
                                 t_settings *settings) {
    mx_print_dir(((t_data *)((t_list *)node->data)->data)->filename,
                 settings);
    if (mx_list_size(inner_node))
        mx_print_total(inner_node);
}

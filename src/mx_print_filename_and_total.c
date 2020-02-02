#include "uls.h"

void mx_print_filename_and_total(t_list *node, t_list *inner_node,
                                 bool is_first, t_settings *settings) {
    if (is_first && settings->R && mx_list_size(inner_node)) {
        mx_print_total(inner_node);
        return;
    }
    mx_print_dir(((t_data *)((t_list *)node->data)->data)->filename, is_first, settings);
    if (mx_list_size(inner_node))
        mx_print_total(inner_node);
}

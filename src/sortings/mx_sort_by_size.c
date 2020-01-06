#include "uls.h"

void mx_sort_by_size(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    mx_sort_list(node, mx_filename_length_comparator);
    while (node) {
        inner_node = ((t_list *)node->data)->next;
        mx_sort_list(inner_node, mx_size_comparator);
        node = node->next;
    }
}

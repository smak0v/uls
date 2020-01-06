#include "uls.h"

void mx_sort_by_creation_time(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    mx_sort_list(node, mx_filename_descending_comparator);
    while (node) {
        inner_node = ((t_list *)node->data)->next;
        mx_sort_list(inner_node, mx_creation_time_comparator);
        node = node->next;
    }
}



#include "uls.h"

void mx_sort_by_name(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    mx_sort_list(node, mx_filename_ascending_comparator);
    while (node) {
        inner_node = ((t_list *)node->data)->next;
        mx_sort_list(inner_node, mx_filename_ascending_comparator);
        node = node->next;
    }
}

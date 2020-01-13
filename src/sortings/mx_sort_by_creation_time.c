#include "uls.h"

void mx_sort_by_creation_time(t_list **list, bool reverse) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    if (!reverse) {
        mx_sort_list(node, mx_creation_time_asc_comparator);
        while (node) {
            inner_node = ((t_list *)node->data)->next;
            mx_sort_list(inner_node, mx_creation_time_asc_comparator);
            node = node->next;
        }
    }
    else {
        mx_sort_list(node, mx_creation_time_desc_comparator);
        while (node) {
            inner_node = ((t_list *)node->data)->next;
            mx_sort_list(inner_node, mx_creation_time_desc_comparator);
            node = node->next;
        }
    }
}



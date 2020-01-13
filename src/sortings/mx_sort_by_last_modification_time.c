#include "uls.h"

void mx_sort_by_last_modification_time(t_list **list, bool reverse) {
    t_list *node = *list;
    t_list *inner = NULL;

    if (!reverse) {
        mx_sort_list(node, mx_last_modification_time_asc_comparator);
        while (node) {
            inner = ((t_list *)node->data)->next;
            mx_sort_list(inner, mx_last_modification_time_asc_comparator);
            node = node->next;
        }
    }
    else {
        mx_sort_list(node, mx_last_modification_time_desc_comparator);
        while (node) {
            inner = ((t_list *)node->data)->next;
            mx_sort_list(inner, mx_last_modification_time_desc_comparator);
            node = node->next;
        }
    }
}

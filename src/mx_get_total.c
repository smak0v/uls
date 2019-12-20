#include "uls.h"

int mx_get_total(t_list **list) {
    int total = 0;
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            data = inner_node->data;
            total += data->blocks_count;
            inner_node = inner_node->next;
        }
        node = node->next;
    }
    return total;
}

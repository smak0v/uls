#include "uls.h"

int mx_get_total(t_list *list) {
    int total = 0;
    t_list *node = list;

    while (node) {
        total += ((t_data *)(node->data))->blocks_count;
        node = node->next;
    }
    return total;
}

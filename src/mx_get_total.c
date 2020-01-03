#include "uls.h"

int mx_get_total(t_list *list) {
    int total = 0;
    t_list *node = list;
    t_data *data = NULL;

    while (node) {
        data = node->data;
        total += data->blocks_count;
        node = node->next;
    }
    return total;
}

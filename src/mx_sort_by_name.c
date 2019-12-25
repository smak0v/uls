#include "uls.h"

static bool compare(void *data_1, void *data_2);

void mx_sort_by_name(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    //t_data *data = NULL;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        mx_sort_list(inner_node, compare);
        // while (inner_node) {
        //     data = inner_node->data;
        //     print_data(data);
        //     inner_node = inner_node->next;
        // }
        node = node->next;
    }
}

static bool compare(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (mx_strcmp(d_1->filename, d_2->filename) > 0)
        return true;
    return false;
}

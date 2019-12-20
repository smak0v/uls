#include "uls.h"

static int get_max_lenght(t_list **list);

void mx_left_align_owner(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;
    int max_len = get_max_lenght(list);
    int len = 0;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            data = inner_node->data;
            len = mx_strlen(data->owner);
            data->owner = mx_l_align(data->owner, max_len - len);
            inner_node = inner_node->next;
        }
        node = node->next;
    }
}

static int get_max_lenght(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;
    int max_len = 0;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            data = inner_node->data;
            if (mx_strlen(data->owner) > max_len)
                max_len = mx_strlen(data->owner);
            inner_node = inner_node->next;
        }
        node = node->next;
    }
    return max_len;
}

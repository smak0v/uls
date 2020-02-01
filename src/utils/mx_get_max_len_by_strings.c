#include "uls.h"

int mx_get_max_len_by_owners(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_strlen(data->owner);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

int mx_get_max_len_by_groups(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_strlen(data->group);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

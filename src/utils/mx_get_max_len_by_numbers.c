#include "uls.h"

int mx_get_max_len_by_sizes(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_numlen(data->file_size);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

int mx_get_max_len_by_xattr_size(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_numlen(data->xattr_value_length);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

int mx_get_max_len_by_inodes(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_unumlen(data->inode);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

#include "uls.h"

int mx_get_max_filename_length(t_list **list) {
    t_list *node = *list;
    int len = 0;
    int max_len = 0;

    while (node) {
        len = mx_strlen(((t_data *)node->data)->filename);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

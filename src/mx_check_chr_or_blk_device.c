#include "uls.h"

bool mx_check_chr_or_blk_device(t_list **list) {
    t_list *node = *list;
    t_data *data = NULL;

    while (node) {
        data = (t_data *)node->data;
        if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode))
            return true;
        node = node->next;
    }
    return false;
}

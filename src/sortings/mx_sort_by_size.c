#include "uls.h"

void mx_sort_by_size(t_list **list, bool reverse) {
    t_list *node = *list;

    if (!reverse)
        mx_sort(node, mx_size_asc_list_cmp, mx_size_asc_cmp);
    else
        mx_sort(node, mx_size_desc_list_cmp, mx_size_desc_cmp);
}

#include "uls.h"

void mx_sort_by_creation_time(t_list **list, bool reverse) {
    t_list *node = *list;

    if (!reverse)
        mx_sort(node, mx_creation_time_desc_list_cmp,
        mx_creation_time_desc_cmp);
    else
        mx_sort(node, mx_creation_time_asc_list_cmp,
        mx_creation_time_asc_cmp);
}

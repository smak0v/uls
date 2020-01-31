#include "uls.h"

void mx_sort_by_name(t_list **list, bool reverse) {
    t_list *node = *list;

    if (!reverse)
        mx_sort(node, mx_filename_asc_list_cmp, mx_filename_asc_cmp);
    else
        mx_sort(node, mx_filename_desc_list_cmp, mx_filename_desc_cmp);
}

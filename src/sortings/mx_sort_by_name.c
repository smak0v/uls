#include "uls.h"

void mx_sort_by_name(t_list **list, bool reverse) {
    if (!reverse)
        mx_sort(list, mx_filename_asc_list_cmp, mx_filename_asc_cmp);
    else
        mx_sort(list, mx_filename_desc_list_cmp, mx_filename_desc_cmp);
}

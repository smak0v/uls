#include "uls.h"

void mx_sort_by_last_modification_time(t_list **list, bool reverse) {
    if (!reverse)
        mx_sort(list, mx_last_modification_time_desc_list_cmp,
        mx_last_modification_time_desc_cmp);
    else
        mx_sort(list, mx_last_modification_time_asc_list_cmp,
        mx_last_modification_time_asc_cmp);
}

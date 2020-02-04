#include "uls.h"

void mx_sort_by_size(t_list **list, t_settings *settings) {
    if (!settings->reverse)
        mx_sort(list, mx_size_asc_list_cmp, mx_size_asc_cmp, settings);
    else
        mx_sort(list, mx_size_desc_list_cmp, mx_size_desc_cmp, settings);
}

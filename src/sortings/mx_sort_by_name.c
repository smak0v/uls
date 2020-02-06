#include "uls.h"

void mx_sort_by_name(t_list **list, t_settings *settings) {
    if (!settings->reverse)
        mx_sort(list, mx_filename_asc_cmp);
    else
        mx_sort(list, mx_filename_desc_cmp);
}

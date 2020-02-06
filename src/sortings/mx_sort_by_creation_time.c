#include "uls.h"

void mx_sort_by_creation_time(t_list **list, t_settings *settings) {
    if (!settings->reverse)
        mx_sort(list, mx_creation_time_desc_cmp);
    else
        mx_sort(list, mx_creation_time_asc_cmp);
}

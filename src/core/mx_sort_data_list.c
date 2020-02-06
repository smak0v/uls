#include "uls.h"

void mx_sort_data_list(t_list **data, t_settings *settings) {
    if (settings->sorting == unsorted)
        mx_sort(data, NULL);
    else if (settings->sorting == size)
        mx_sort_by_size(data, settings);
    else if (settings->sorting == chg_time)
        mx_sort_by_last_changed_time(data, settings);
    else if (settings->sorting == acc_time)
        mx_sort_by_last_access_time(data, settings);
    else if (settings->sorting == crt_time)
        mx_sort_by_creation_time(data, settings);
    else if (settings->sorting == mod_time)
        mx_sort_by_last_modification_time(data, settings);
    else
        mx_sort_by_name(data, settings);
}

#include "uls.h"

bool mx_creation_time_asc_list_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)((t_list *)data_1)->data;
    t_data *d_2 = (t_data *)((t_list *)data_2)->data;

    if (d_1->creation_time > d_2->creation_time)
        return true;
    return false;
}

bool mx_last_modification_time_asc_list_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)((t_list *)data_1)->data;
    t_data *d_2 = (t_data *)((t_list *)data_2)->data;

    if (!mx_strcmp(d_1->filename, FILES) || !mx_strcmp(d_2->filename, FILES))
        return false;
    if (d_1->last_modified == d_2->last_modified) {
        if (d_1->last_modified_nsec == d_2->last_modified_nsec)
            return mx_filename_desc_cmp(data_1, data_2);
        if (d_1->last_modified_nsec > d_2->last_modified_nsec)
            return true;
        return false;
    }
    return (d_1->last_modified > d_2->last_modified) ? true : false;
}

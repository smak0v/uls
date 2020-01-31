#include "uls.h"

bool mx_filename_asc_list_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)((t_list *)data_1)->data;
    t_data *d_2 = (t_data *)((t_list *)data_2)->data;

    if (!mx_strcmp(d_1->filename, FILES) || !mx_strcmp(d_2->filename, FILES))
        return false;
    if (mx_strcmp(d_1->filename, d_2->filename) > 0)
        return true;
    return false;
}

bool mx_filename_desc_list_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)((t_list *)data_1)->data;
    t_data *d_2 = (t_data *)((t_list *)data_2)->data;

    if (!mx_strcmp(d_1->filename, FILES) || !mx_strcmp(d_2->filename, FILES))
        return false;
    if (mx_strcmp(d_1->filename, d_2->filename) < 0)
        return true;
    return false;
}

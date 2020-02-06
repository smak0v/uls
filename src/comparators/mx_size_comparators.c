#include "uls.h"

bool mx_size_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->file_size == d_2->file_size)
        return mx_filename_asc_cmp(data_1, data_2);
    return (d_1->file_size < d_2->file_size) ? true : false;
}

bool mx_size_desc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->file_size == d_2->file_size)
        return mx_filename_desc_cmp(data_1, data_2);
    return (d_1->file_size > d_2->file_size) ? true : false;
}

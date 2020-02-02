#include "uls.h"

bool mx_filename_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (!mx_strcmp(d_1->filename, "./") || !mx_strcmp(d_2->filename, "./"))
        return false;
    if (!mx_strcmp(d_1->filename, "../") || !mx_strcmp(d_2->filename, "../"))
        return false;
    if (mx_strcmp(d_1->filename, d_2->filename) > 0)
        return true;
    return false;
}

bool mx_filename_desc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (!mx_strcmp(d_1->filename, "./") || !mx_strcmp(d_2->filename, "./"))
        return false;
    if (!mx_strcmp(d_1->filename, "../") || !mx_strcmp(d_2->filename, "../"))
        return false;
    if (mx_strcmp(d_1->filename, d_2->filename) < 0)
        return true;
    return false;
}

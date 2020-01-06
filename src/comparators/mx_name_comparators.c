#include "uls.h"

bool mx_filename_ascending_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (mx_strcmp(d_1->filename, d_2->filename) > 0)
        return true;
    return false;
}

bool mx_filename_descending_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (mx_strcmp(d_1->filename, d_2->filename) < 0)
        return true;
    return false;
}

bool mx_filename_length_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (mx_strlen(d_1->filename) >= mx_strlen(d_2->filename))
        return true;
    return false;
}

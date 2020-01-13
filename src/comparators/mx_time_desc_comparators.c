#include "uls.h"

bool mx_creation_time_desc_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->creation_time > d_2->creation_time)
        return true;
    return false;
}

bool mx_last_access_time_desc_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_access > d_2->last_access)
        return true;
    return false;
}

bool mx_last_modification_time_desc_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_modified > d_2->last_modified)
        return true;
    return false;
}

bool mx_last_changed_time_desc_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_changed > d_2->last_changed)
        return true;
    return false;
}

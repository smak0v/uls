#include "uls.h"

bool mx_creation_time_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->creation_time == d_2->creation_time) {
        if (d_1->creation_time_nsec == d_2->creation_time_nsec)
            return mx_filename_asc_cmp(data_1, data_2);
        if (d_1->creation_time_nsec > d_2->creation_time_nsec)
            return true;
        return false;
    }
    return (d_1->creation_time > d_2->creation_time) ? true : false;
}

bool mx_last_access_time_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_access == d_2->last_access) {
        if (d_1->last_access_nsec == d_2->last_access_nsec)
            return mx_filename_asc_cmp(data_1, data_2);
        if (d_1->last_access_nsec > d_2->last_access_nsec)
            return true;
        return false;
    }
    return (d_1->last_access > d_2->last_access) ? true : false;
}

bool mx_last_modification_time_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_modified == d_2->last_modified) {
        if (d_1->last_modified_nsec == d_2->last_modified_nsec)
            return mx_filename_desc_cmp(data_1, data_2);
        if (d_1->last_modified_nsec > d_2->last_modified_nsec)
            return true;
        return false;
    }
    return (d_1->last_modified > d_2->last_modified) ? true : false;
}

bool mx_last_changed_time_asc_cmp(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->last_changed == d_2->last_changed) {
        if (d_1->last_changed_nsec == d_2->last_changed_nsec)
            return mx_filename_asc_cmp(data_1, data_2);
        if (d_1->last_changed_nsec > d_2->last_changed_nsec)
            return true;
        return false;
    }
    return (d_1->last_changed > d_2->last_changed) ? true : false;
}

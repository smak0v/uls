#include "uls.h"

bool mx_size_comparator(void *data_1, void *data_2) {
    t_data *d_1 = (t_data *)data_1;
    t_data *d_2 = (t_data *)data_2;

    if (d_1->file_size < d_2->file_size)
        return true;
    return false;
}

#include "uls.h"

static bool errors_filename_comparator(void *data_1, void *data_2);

void mx_sort_errors(t_list **errors) {
    t_list *node = *errors;

    mx_sort_list(node, errors_filename_comparator);
}

static bool errors_filename_comparator(void *data_1, void *data_2) {
    t_error *file_1 = (t_error *)data_1;
    t_error *file_2 = (t_error *)data_2;

    if (mx_strcmp(file_1->filename, file_2->filename) > 0)
        return true;
    return false;
}

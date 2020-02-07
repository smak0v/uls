#include "uls.h"

static bool errors_filename_comparator(void *data_1, void *data_2) {
    t_error *error_1 = (t_error *)data_1;
    t_error *error_2 = (t_error *)data_2;

    if (mx_strcmp(error_1->filename, error_2->filename) > 0)
        return true;
    return false;
}

void mx_sort_errors(t_list **errors) {
    t_list *node = *errors;

    mx_sort_list(node, errors_filename_comparator);
}

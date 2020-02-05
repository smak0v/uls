#include "uls.h"

static bool errors_filename_comparator(void *data_1, void *data_2) {
    char *file_1 = (char *)data_1;
    char *file_2 = (char *)data_2;

    if (mx_strcmp(file_1, file_2) > 0)
        return true;
    return false;
}

void mx_sort_errors(t_list **errors) {
    t_list *node = *errors;

    mx_sort_list(node, errors_filename_comparator);
}

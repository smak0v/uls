#include "uls.h"

static void print_file_errors(t_list **errors);
static void print_dir_errors(t_list **errors);

void mx_print_errors(t_list *errors) {
    mx_sort_errors(&errors);
    print_file_errors(&errors);
    print_dir_errors(&errors);
}

static void print_file_errors(t_list **errors) {
    t_list *node = *errors;
    t_error *error = NULL;

    while (node) {
        error = (t_error *)node->data;
        if (!error->is_dir)
            mx_print_uls_error(error->filename, error->error);
        node = node->next;
    }
}

static void print_dir_errors(t_list **errors) {
    t_list *node = *errors;
    t_error *error = NULL;

    while (node) {
        error = (t_error *)node->data;
        if (error->is_dir) {
            mx_printstr(error->filename);
            mx_printstr_endl(":");
            mx_print_uls_error(error->filename, error->error);
        }
        node = node->next;
    }
}

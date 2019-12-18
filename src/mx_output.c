#include "uls.h"

static void output_table_mode(t_list **data) {
    // to do
}

static void output_commas_mode(t_list **data) {
    // to do
}

static void output_columns_mode(t_list **data) {
    // to do
}

void mx_process_output(t_list **data, char **flags) {
    if (mx_search_strarr(flags, "l")) {
        output_table_mode(data);
    }
    else if (mx_search_strarr(flags, "m")) {
        output_commas_mode(data);
    }
    else {
        output_columns_mode(data);
    }
}
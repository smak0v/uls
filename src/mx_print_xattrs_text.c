#include "uls.h"

static void print_xattrs(t_data *data, t_max_len *max_len);

void mx_print_xattrs_text(t_data *data, t_settings *settings,
t_max_len *max_len) {
    if (settings->print_xattr && data->xattr_text)
        print_xattrs(data, max_len);
}

static void print_xattrs(t_data *data, t_max_len *max_len) {
    int max_num_len = mx_numlen(data->xattr_value_length);

    mx_printchar('\t');
    mx_printstr(data->xattr_text);
    mx_printchar('\t');
    mx_print_spaces(2);
    mx_print_spaces(max_num_len - max_len->xattrs_sizes);
    mx_printint_endl(data->xattr_value_length);
}

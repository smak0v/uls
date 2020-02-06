#include "uls.h"

static void print_xattrs(t_data *data, t_max_len *max_len,
                         t_settings *settings) {
    int max_num_len = mx_numlen(data->xattr_value_length);

    if (!max_num_len && !(data->xattr_value_length))
        max_num_len = 1;
    mx_printchar('\t');
    mx_printstr(data->xattr_text);
    mx_printchar('\t');
    mx_print_spaces(2);
    if (settings->a || settings->A)
        mx_print_spaces(max_len->xattrs_sizes - max_num_len + 1);
    else
        mx_print_spaces(max_len->xattrs_sizes - max_num_len);
    mx_printint(data->xattr_value_length);
    if (settings->format_size)
        mx_printstr("B \n");
    else
        mx_printstr(" \n");
}

void mx_print_xattrs_text(t_data *data, t_settings *settings,
                          t_max_len *max_len) {
    if (settings->print_xattr && data->xattr_text)
        print_xattrs(data, max_len, settings);
}

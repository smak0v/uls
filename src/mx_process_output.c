#include "uls.h"

static void process_sorting(t_list **data, t_settings *settings) {
    if (settings->sorting == unsorted)
        return;
    else if (settings->sorting == size)
        mx_sort_by_size(data, settings->reverse);
    else if (settings->sorting == chg_time)
        mx_sort_by_last_changed_time(data, settings->reverse);
    else if (settings->sorting == acc_time)
        mx_sort_by_last_access_time(data, settings->reverse);
    else if (settings->sorting == crt_time)
        mx_sort_by_creation_time(data, settings->reverse);
    else if (settings->sorting == mod_time)
        mx_sort_by_last_modification_time(data, settings->reverse);
    else if (settings->sorting == names)
        mx_sort_by_name(data, settings->reverse);
}

void mx_process_output(t_list **data, t_settings *settings, char **flags) {
    process_sorting(data, settings);
    if (isatty(1) || mx_has_output_format_flag(flags)) {
        if (settings->mode == columns) {
            if (settings->print_xcols)
                mx_print_x_columns(data, settings);
            else
                mx_print_columns(data, settings);
        }
        else if (settings->mode == table)
            mx_print_long(data, settings);
        else if (settings->mode == commas)
            mx_print_stream(data, settings);
        else
            mx_print_force(data, settings);
    } else
        mx_print_force(data, settings);
}

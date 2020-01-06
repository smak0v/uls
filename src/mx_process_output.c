#include "uls.h"

static void process_sorting(t_list **data, t_settings *settings) {
    if (settings->sorting == size)
        mx_sort_by_size(data);
    else if (settings->sorting == mod_time)
        mx_sort_by_last_modification_time(data);
    else if (settings->sorting == names)
        mx_sort_by_name(data);
}

void mx_process_output(t_list **data, t_settings *settings) {
    t_mode_enum mode;

    process_sorting(data, settings);
    if (isatty(1)) {
        if ((int)(mode = columns) == settings->mode)
            mx_print_columns(data, settings->not_found);
        else if ((int)(mode = table) == settings->mode)
            mx_print_long(data, settings->not_found);
        else if ((int)(mode = commas) == settings->mode)
            mx_print_names(data, ", ", settings->not_found);
        else
            mx_print_names(data, "\n", settings->not_found);
    } else
        mx_print_names(data, "\n", settings->not_found);
}

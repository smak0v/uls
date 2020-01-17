#include "uls.h"

static void process_sorting(t_list **data, t_settings *settings) {
    if (settings->sorting == size)
        mx_sort_by_size(data, settings->reverse);
    else if (settings->sorting == mod_time)
        mx_sort_by_last_modification_time(data, settings->reverse);
    else if (settings->sorting == names)
        mx_sort_by_name(data, settings->reverse);
}

void mx_process_output(t_list **data, t_settings *settings, char **flags) {
    t_mode_enum mode;

    process_sorting(data, settings);
    if (isatty(1) || mx_has_output_format_flag(flags)) {
        if ((int)(mode = columns) == settings->mode) {
            if (settings->print_xcols)
                mx_print_x_columns(data, settings);
            else
                mx_print_columns(data, settings);
        }
        else if ((int)(mode = table) == settings->mode)
            mx_print_long(data, settings);
        else if ((int)(mode = commas) == settings->mode)
            mx_print_stream(data, settings);
        else
            mx_print_force(data, settings);
    } else
        mx_print_force(data, settings);
}

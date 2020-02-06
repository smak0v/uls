#include "uls.h"

void mx_proccess_output(t_list **list, t_settings *settings) {
    if (settings->is_atty || settings->has_output_format_flag) {
        if (settings->mode == columns) {
            if (settings->print_xcols)
                mx_print_x_columns(list, settings);
            else
                mx_print_columns(list, settings);
        }
        else if (settings->mode == table)
            mx_print_long(list, settings);
        else if (settings->mode == commas)
            mx_print_stream(list, settings);
        else
            mx_print_force(list, settings);
    } else
        mx_print_force(list, settings);
}

#include "uls.h"

void mx_process_output(t_list **data, t_settings *settings) {
    t_mode_enum mode;

    mx_sort_by_name(data);
    if ((int)(mode = columns) == settings->mode)
        mx_print_columns(data);
    else if ((int)(mode = table) == settings->mode)
        mx_print_long(data);
    else if ((int)(mode = commas) == settings->mode)
        mx_print_names(data, ", ");
    else
        mx_print_names(data, "\n");
}

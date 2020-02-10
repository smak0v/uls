#include "uls.h"

static void print_type_sign(t_data *data) {
    if (MX_IS_DIR(data->mode))
        mx_printchar('/');
    else if (MX_IS_REG(data->mode) && MX_IS_EXEC(data->mode))
        mx_printchar('*');
    else if (MX_IS_LNK(data->mode))
        mx_printchar('@');
    else if (MX_IS_SOCK(data->mode))
        mx_printchar('=');
    else if (MX_IS_WHT(data->mode))
        mx_printchar('%');
    else if (MX_IS_FIFO(data->mode))
        mx_printchar('|');
}

void mx_print_filename(t_data *data, t_settings *settings) {
    if (settings->colored && settings->is_atty) {
        mx_print_colored(data);
        if (settings->w)
            mx_printstr(data->filename);
        else
            mx_print_non_printable_str(data->filename);
        mx_printstr("\033[0m");
    }
    else {
        if (!settings->is_atty || settings->w)
            mx_printstr(data->filename);
        else
            mx_print_non_printable_str(data->filename);
    }
    if (settings->append_slash && MX_IS_DIR(data->mode))
        mx_printchar('/');
    else if (settings->append_type_sign)
        print_type_sign(data);
}

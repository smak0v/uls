#include "uls.h"

static void print_type_sign(t_data *data) {
    if (data->permissions[0] == 'd')
        mx_printchar('/');
    else if (data->permissions[0] == '-' && MX_IS_EXEC(data->mode))
        mx_printchar('*');
    else if (data->permissions[0] == 'l')
        mx_printchar('@');
    else if (data->permissions[0] == 's')
        mx_printchar('=');
    else if (data->permissions[0] == 'w')
        mx_printchar('%');
    else if (data->permissions[0] == 'p')
        mx_printchar('|');
}

void mx_print_filename(t_data *data, t_settings *settings) {
    if (settings->colored && settings->is_atty) {
        mx_print_colored(data);
        mx_printstr(data->filename);
        mx_printstr("\033[0m");
    }
    else
        mx_printstr(data->filename);
    if (settings->append_slash && data->permissions[0] == 'd')
        mx_printchar('/');
    else if (settings->append_type_sign)
        print_type_sign(data);
}

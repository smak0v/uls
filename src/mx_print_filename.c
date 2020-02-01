#include "uls.h"

void mx_print_filename(t_data *data, t_settings *settings) {
    char *tmp = NULL;

    if (settings->colored && isatty(1)) {
        mx_print_colored(data);
        tmp = mx_strndup(data->filename, mx_strlen(data->filename) - 1);
        mx_printstr(tmp);
        mx_strdel(&tmp);
        mx_printstr("\033[0m");
        tmp = mx_strndup(data->filename + mx_strlen(data->filename) - 1, 1);
        mx_printstr(tmp);
        mx_strdel(&tmp);
    }
    else {
        mx_printstr(data->filename);
    }
}

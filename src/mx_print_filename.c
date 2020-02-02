#include "uls.h"

static bool check_last_symbol(t_data *data) {
    for (int i = mx_strlen(data->filename); i >= 0; i--)
        for (int j = 0; j < mx_strlen(LAST_SYMBOLS); j++)
            if (data->filename[i] == LAST_SYMBOLS[j])
                return true;
    return false;
}

static void print(t_data *data) {
    char *tmp = mx_strndup(data->filename, mx_strlen(data->filename) - 1);

    mx_printstr(tmp);
    mx_strdel(&tmp);
    mx_printstr("\033[0m");
    tmp = mx_strndup(data->filename + mx_strlen(data->filename) - 1, 1);
    mx_printstr(tmp);
    mx_strdel(&tmp);
}

void mx_print_filename(t_data *data, t_settings *settings) {
    if (settings->colored && settings->mode == columns && isatty(1)) {
        mx_print_colored(data);
        print(data);
    }
    else if (settings->colored && settings->mode != columns && isatty(1)) {
        mx_print_colored(data);
        if (check_last_symbol(data))
            print(data);
        else {
            mx_printstr(data->filename);
            mx_printstr("\033[0m");
        }
    }
    else
        mx_printstr(data->filename);
}

#include "uls.h"

void mx_print_filename(t_data *data, t_settings *settings) {
    if (settings->colored && isatty(1))
        mx_print_colored(data);
    mx_printstr(data->filename);
    if (isatty(1))
        mx_printstr("\033[0m");
}

#include "uls.h"

void mx_print_dir(char *dirname, bool *is_first, t_settings *settings) {
    int tmp = mx_strcmp(FILES, dirname);

    if (!tmp || (settings->R && *is_first)) {
        *is_first = false;
        if (settings->has_many_file_arguments && tmp) {
            mx_printstr(dirname);
            mx_printstr(":\n");
        }
        return;
    }
    mx_printstr(dirname);
    mx_printstr(":\n");
}

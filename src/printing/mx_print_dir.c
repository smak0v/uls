#include "uls.h"

void mx_print_dir(char *dirname, t_settings *settings) {
    int tmp = mx_strcmp(FILES, dirname);

    if (!tmp || settings->is_first) {
        if (settings->has_many_file_arguments && tmp) {
            mx_printstr(dirname);
            mx_printstr(":\n");
        }
        return;
    }
    mx_printstr(dirname);
    mx_printstr(":\n");
}

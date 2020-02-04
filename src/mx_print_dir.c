#include "uls.h"

void mx_print_dir(char *dirname, bool *is_first, t_settings *settings) {
    if (mx_strcmp(FILES, dirname) || (settings->R && *is_first)) {
        *is_first = false;
        return;
    }
    mx_printstr(dirname);
    mx_printstr(":\n");
}

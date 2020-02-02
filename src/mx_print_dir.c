#include "uls.h"

void mx_print_dir(char *dirname, bool *is_first, t_settings *settings) {
    if (settings->R && *is_first) {
        *is_first = false;
        return;
    }
    if (*is_first)
        *is_first = false;
    mx_printstr(dirname);
    mx_printstr(":\n");
}

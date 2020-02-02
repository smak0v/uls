#include "uls.h"

void mx_print_dir(char *dirname, bool is_first, t_settings *settings) {
    if (is_first && settings->R)
        return;
    mx_printstr(dirname);
    mx_printstr(":\n");
}

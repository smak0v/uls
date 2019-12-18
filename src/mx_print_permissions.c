#include "uls.h"

void mx_print_permissions(mode_t mode) {
    char *permissions = mx_get_permissions(mode);

    mx_printstr(permissions);
    mx_strdel(&permissions);
}

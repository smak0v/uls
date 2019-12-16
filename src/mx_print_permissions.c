#include "uls.h"

void mx_print_permissions(unsigned short mode) {
    char *permissions = mx_get_permissions(mode);

    mx_printstr(permissions);
    mx_strdel(&permissions);
}

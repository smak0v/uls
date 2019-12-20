#include "uls.h"

void mx_print_acl_xattr_or_nothing(t_data *data) {
    if (data->xattr_text)
        mx_printstr("@ ");
    else if (data->acl_text)
        mx_printstr("+ ");
    else
        mx_print_spaces(2);
}

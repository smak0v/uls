#include "uls.h"

void mx_print_acl_xattr_or_nothing(t_data *data) {
    if (data->xattr_value_length >= 0)
        mx_printstr("@ ");
    else if (data->has_acl)
        mx_printstr("+ ");
    else
        mx_print_spaces(2);
}

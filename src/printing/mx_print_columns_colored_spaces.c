#include "uls.h"

void mx_print_columns_colored_spaces(t_settings *settings, t_data *prev,
                                     t_columns_info *info) {
    if (settings->append_slash || settings->append_type_sign) {
        if (prev->permissions[0] == '-'
            || prev->permissions[0] == 'b'
            || prev->permissions[0] == 'c')
            mx_print_spaces(info->max_len - mx_strlen(prev->filename) + 2);
        else
            mx_print_spaces(info->max_len - mx_strlen(prev->filename) + 1);
        }
    else
        mx_print_spaces(info->max_len - mx_strlen(prev->filename) + 1);
}

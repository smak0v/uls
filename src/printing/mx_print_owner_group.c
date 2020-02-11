#include "uls.h"

void mx_print_owner_group(t_settings *settings, t_data *data, t_max_len *len) {
    if (!settings->omit_owner) {
        mx_printstr(data->owner);
        mx_print_spaces(len->owners - mx_strlen(data->owner));
    }
    if ((!settings->omit_owner && !settings->omit_group)
        && !settings->omit_group && !settings->omit_owner)
        mx_print_spaces(2);
    if (!settings->omit_group) {
        mx_printstr(data->group);
        mx_print_spaces(len->groups - mx_strlen(data->group));
    }
}

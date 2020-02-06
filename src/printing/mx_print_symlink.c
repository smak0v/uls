#include "uls.h"

void mx_print_symlink(t_data *data) {
    if (data->symlink) {
        mx_printstr(" -> ");
        mx_printstr(data->symlink);
    }
}

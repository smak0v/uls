#include "uls.h"

static void print_colored_dir(char *perms) {
    if (perms[8] == 'w' && (perms[9] == 't' || perms[9] == 'T'))
        mx_printstr("\033[30;42m");
    else if (perms[8] == 'w' && perms[9] == 'x')
        mx_printstr("\033[30;43m");
    else
        mx_printstr("\033[34m");
}

void mx_print_colored(t_data *data) {
    if (data->permissions[3] == 's' || data->permissions[3] == 'S')
        mx_printstr("\033[30;41m");
    else if (data->permissions[6] == 's' || data->permissions[6] == 'S')
        mx_printstr("\033[30;46m");
    else if (MX_IS_BLK(data->mode))
        mx_printstr("\033[34;46m");
    else if (MX_IS_CHR(data->mode))
        mx_printstr("\033[34;43m");
    else if (MX_IS_DIR(data->mode))
        print_colored_dir(data->permissions);
    else if (MX_IS_LNK(data->mode))
        mx_printstr("\033[35m");
    else if (MX_IS_SOCK(data->mode))
        mx_printstr("\033[32m");
    else if (MX_IS_FIFO(data->mode))
        mx_printstr("\033[33m");
    else if (MX_IS_WHT(data->mode))
        mx_printstr("\033[36m");
    else if (MX_IS_EXEC(data->mode))
        mx_printstr("\033[31m");
}

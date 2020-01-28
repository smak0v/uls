#include "uls.h"

void mx_append_slash(t_data **info, t_settings *settings) {
    char *tmp = NULL;

    if ((*info)->permissions[0] == 'd')
        tmp = mx_strjoin((*info)->filename, "/");
    else if (settings->mode == columns)
        tmp = mx_strjoin((*info)->filename, " ");
    if (tmp) {
        mx_strdel(&(*info)->filename);
        (*info)->filename = tmp;
    }
}

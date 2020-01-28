#include "uls.h"

void mx_append_type_sign(t_st st, t_data **info, t_settings *settings) {
    char *tmp = NULL;

    if ((*info)->permissions[0] == 'd')
        tmp = mx_strjoin((*info)->filename, "/");
    else if ((*info)->permissions[0] == '-' && MX_IS_EXEC(st.st_mode))
        tmp = mx_strjoin((*info)->filename, "*");
    else if ((*info)->permissions[0] == 'l')
        tmp = mx_strjoin((*info)->filename, "@");
    else if ((*info)->permissions[0] == 's')
        tmp = mx_strjoin((*info)->filename, "=");
    else if ((*info)->permissions[0] == 'w')
        tmp = mx_strjoin((*info)->filename, "%");
    else if ((*info)->permissions[0] == 'p')
        tmp = mx_strjoin((*info)->filename, "|");
    else if (settings->mode == columns)
        tmp = mx_strjoin((*info)->filename, " ");
    if (tmp) {
        mx_strdel(&(*info)->filename);
        (*info)->filename = tmp;
    }
}

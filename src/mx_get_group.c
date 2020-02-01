#include "uls.h"

char *mx_get_group(gid_t st_gid, t_settings *settings) {
    struct group *group_ptr = NULL;

    if (settings->n)
        return mx_itoa(st_gid);
    group_ptr = getgrgid(st_gid);
    if (group_ptr)
        return mx_strdup(group_ptr->gr_name);
    else
        return mx_itoa(st_gid);
}

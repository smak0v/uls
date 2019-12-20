#include "uls.h"

char *mx_get_group(gid_t st_gid) {
    char *group = NULL;
    struct group *group_ptr = getgrgid(st_gid);

    if (group_ptr)
        group = mx_strdup(group_ptr->gr_name);
    else
        group = mx_itoa(st_gid);
    return group;
}

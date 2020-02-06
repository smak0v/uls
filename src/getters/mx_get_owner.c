#include "uls.h"

char *mx_get_owner(uid_t st_uid, t_settings *settings) {
    struct passwd *passwd_ptr = NULL;

    if (settings->n)
        return mx_itoa(st_uid);
    passwd_ptr = getpwuid(st_uid);
    if (passwd_ptr)
        return mx_strdup(passwd_ptr->pw_name);
    else
        return mx_itoa(st_uid);
}

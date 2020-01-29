#include "uls.h"

char *mx_get_symlink(char *dirname, off_t st_size) {
    char *symlink = mx_strnew(st_size);
    ssize_t size = readlink(dirname, symlink, st_size + 1);

    if (size > 0)
        return symlink;
    mx_strdel(&symlink);
    return NULL;
}

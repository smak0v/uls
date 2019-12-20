#include "uls.h"

char mx_get_file_type(mode_t mode) {
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISSOCK(mode))
        return 's';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISWHT(mode))
        return 'w';
    return '-';
}

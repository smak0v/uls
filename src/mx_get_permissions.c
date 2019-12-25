#include "uls.h"

char *mx_get_permissions(mode_t mode) {
    char *permissions = mx_strnew(10);

    permissions[0] = mx_get_file_type(mode);
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_ISVTX) ? 'T' : ((mode & S_IXOTH) ? 'x' : '-');
    return permissions;
}

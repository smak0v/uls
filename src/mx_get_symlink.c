#include "uls.h"

char *mx_get_symlink(t_data * data) {
    char *symlink = NULL;
    ssize_t size = 0;

    if (data->permissions[0] == 'l') {
        symlink = mx_strnew(data->file_size);
        size = readlink(data->full_filename, symlink, data->file_size + 1);
        if (size > 0)
            return symlink;
        mx_strdel(&symlink);
        return NULL;
    }
    return NULL;
}

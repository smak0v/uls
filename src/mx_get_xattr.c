#include "uls.h"

char *mx_get_xattr(char *dirname) {
    ssize_t len = listxattr(dirname, NULL, 0, XATTR_SHOWCOMPRESSION);
    char *buffer = NULL;

    if ((len < 0) || (len == 0))
        return NULL;
    buffer = mx_strnew(len);
    listxattr(dirname, buffer, len, XATTR_SHOWCOMPRESSION);
    return buffer;
}

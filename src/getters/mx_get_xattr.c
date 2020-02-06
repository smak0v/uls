#include "uls.h"

char *mx_get_xattr(char *dirname, ssize_t *length) {
    ssize_t len = listxattr(dirname, NULL, 0, XATTR_NOFOLLOW);
    ssize_t xattr_value_length = 0;
    char *buffer = NULL;

    if (len <= 0)
        return NULL;
    buffer = mx_strnew(len);
    listxattr(dirname, buffer, len, XATTR_NOFOLLOW);
    xattr_value_length = getxattr(dirname, buffer, NULL, 0, 0, 0);
    if (len && buffer) {
        if (xattr_value_length >= 0) {
            *length = xattr_value_length;
            return buffer;
        }
        *length = 0;
        return buffer;
    }
    mx_strdel(&buffer);
    return NULL;
}

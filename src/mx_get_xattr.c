#include "uls.h"

static ssize_t get_xattr_size(char *dirname, char *buffer);

char *mx_get_xattr(char *dirname, ssize_t *length) {
    ssize_t len = listxattr(dirname, NULL, 0, XATTR_NOFOLLOW);
    char *buffer = NULL;
    int xattr_value_length = 0;

    if (len <= 0)
        return NULL;
    buffer = mx_strnew(len);
    listxattr(dirname, buffer, len, XATTR_NOFOLLOW);
    xattr_value_length = get_xattr_size(dirname, buffer);
    if (xattr_value_length >= 0) {
        *length = xattr_value_length;
        return buffer;
    }
    return NULL;
}

static ssize_t get_xattr_size(char *dirname, char *buffer) {
    ssize_t xattr_len = getxattr(dirname, buffer, NULL, 0, 0, 0);

    return xattr_len;
}

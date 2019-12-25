#include "libmx.h"

int mx_strlen(const char *s) {
    int length = 0;
    int i = 0;

    if (s) {
        while (s[i++])
            length++;
        return length;
    }
    return 0;
}

int mx_strarr_len(char **strarr) {
    int len = 0;

    if (!strarr) {
        return len;
    }

    while (strarr[len]) {
        len++;
    }

    return len;
}

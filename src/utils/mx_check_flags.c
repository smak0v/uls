#include "uls.h"

char *mx_check_flag(char **flags) {
    char **ptr = flags;
    int index = 0;

    while (*ptr) {
        index = mx_get_char_index(ALLOWED_FLAGS, **ptr);
        if (index == -1)
            return *ptr;
        ptr++;
    }
    return NULL;
}

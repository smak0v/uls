#include "uls.h"

bool mx_search_strarr(char **strarr, char *str) {
    if (!strarr)
        return false;
    for (int i = 0; strarr[i]; ++i)
        if (mx_strcmp(strarr[i], str) == 0)
            return true;
    return false;
}

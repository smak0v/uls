#include "uls.h"

int mx_check_reverse(char **flags) {
    for (int i = 0; flags[i]; i++) {
        if (mx_strcmp(flags[i], "r") == 0)
            return 1;
    }
    return 0;
}

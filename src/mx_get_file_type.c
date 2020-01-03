#include "uls.h"

char mx_get_file_type(mode_t mode) {
    if (IS_BLK(mode))
        return 'b';
    if (IS_CHR(mode))
        return 'c';
    if (IS_DIR(mode))
        return 'd';
    if (IS_LNK(mode))
        return 'l';
    if (IS_SOCK(mode))
        return 's';
    if (IS_FIFO(mode))
        return 'p';
    if (IS_WHT(mode))
        return 'w';
    return '-';
}

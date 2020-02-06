#include "uls.h"

char mx_get_file_type(mode_t mode) {
    if (MX_IS_BLK(mode))
        return 'b';
    if (MX_IS_CHR(mode))
        return 'c';
    if (MX_IS_DIR(mode))
        return 'd';
    if (MX_IS_LNK(mode))
        return 'l';
    if (MX_IS_SOCK(mode))
        return 's';
    if (MX_IS_FIFO(mode))
        return 'p';
    if (MX_IS_WHT(mode))
        return 'w';
    return '-';
}

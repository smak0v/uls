#include "uls.h"

int mx_uls_h_get_pow(off_t st_size) {
    off_t number = st_size;
    int pow = 0;

    while (number >= 1000) {
        number /= 1024;
        pow += 10;
    }
    return pow;
}

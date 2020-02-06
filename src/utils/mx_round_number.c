#include "uls.h"

int mx_round_number(double g) {
    off_t result = 0;;
    
    if (((off_t)(g * 10) % 10) >= 5)
        result = (off_t)(g * 10) / 10 + 1;
    else
        result = (off_t)(g * 10) / 10;
    return result;
}

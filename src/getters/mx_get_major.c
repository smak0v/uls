#include "uls.h"

char *mx_get_major(int st_rdev) {
    return mx_itoa((int)(((unsigned int)st_rdev >> 24) & 0xff));
}

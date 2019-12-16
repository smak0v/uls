#include "uls.h"

char *mx_format_time(char *lm_time) {
    char *lm_time_copy = lm_time;

    lm_time_copy += 4;
    return mx_strndup(lm_time_copy, 12);
}

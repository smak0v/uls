#include "uls.h"

void mx_print_non_printable_str(const char *s) {
    char tmp = '?';
    int i = 0;

    if (s) {
        while (s[i]) {
            (s[i] > 31 && s[i] < 127) ? write(1, &s[i], 1) : write(1, &tmp, 1);
            i++;
        }
    }
}

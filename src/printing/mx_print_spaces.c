#include "uls.h"

void mx_print_spaces(int count) {
    if (count > 0)
        while (count--)
            mx_printchar(' ');
}

#include "uls.h"

void mx_print_total(t_list *list) {
    char *total = mx_itoa(mx_get_total(list));

    mx_printstr("total ");
    mx_printstr_endl(total);
    mx_strdel(&total);
}

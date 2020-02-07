#include "uls.h"

void mx_find_flags(t_settings *settings, char **flags) {
    for (int i = 0; flags[i]; ++i) {
        if (flags[i][0] == 'r')
            settings->reverse = true;
        else if (flags[i][0] == 'n')
            settings->n = true;
        else if (flags[i][0] == 'h')
            settings->format_size = true;
        else if (flags[i][0] == '@')
            settings->print_xattr = true;
        else if (flags[i][0] == 'x')
            settings->print_xcols = true;
        else if (flags[i][0] == 'T')
            settings->full_time = true;
        else if (flags[i][0] == 'p') {
            settings->append_slash = true;
            settings->append_type_sign = false;
        }
        else
            mx_find_flags_2(settings, flags[i][0]);
    }
}

void mx_find_flags_2(t_settings *settings, char flag) {
    if (flag == 'o')
        settings->omit_group = true;
    else if (flag == 'g')
        settings->omit_owner = true;
    else if (flag == 'G')
        settings->colored = true;
    else if (flag == 'i')
        settings->print_inode = true;
    else if (flag == 'F') {
        settings->append_type_sign = true;
        settings->append_slash = false;
    }
    else if (flag == 'R')
        settings->R = true;
    else if (flag == 'A')
        settings->A = true;
    else if (flag == 'a' || flag == 'f')
        settings->a = true;
    else
        mx_find_flags_3(settings, flag);
}

void mx_find_flags_3(t_settings *settings, char flag) {
    if (flag == 'U')
        settings->time = crt;
    else if (flag == 'u')
        settings->time = acc;
    else if (flag == 'c')
        settings->time = chg;
}

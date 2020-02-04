#include "uls.h"

static bool find_flag(char **flags, char f) {
    for (int i = 0; flags[i]; i++)
        if (flags[i][0] == f)
            return true;
    return false;
}


static void find_flags_3(t_settings *s, char flag) {
    if (flag == 'U')
        s->time = crt;
    else if (flag == 'u')
        s->time = acc;
    else if (flag == 'c')
        s->time = chg;
}

static void find_flags_2(t_settings *s, char flag) {
    if (flag == 'o')
        s->omit_group = true;
    if (flag == 'g')
        s->omit_owner = true;
    if (flag == 'G')
        s->colored = true;
    if (flag == 'i')
        s->print_inode = true;
    if (flag == 'F') {
        s->append_type_sign = true;
        s->append_slash = false;
    }
    if (flag == 'R')
        s->R = true;
    if (flag == 'A')
        s->A = true;
    if (flag == 'a' || flag == 'f')
        s->a = true;
    find_flags_3(s, flag);
}

static void find_flags(t_settings *s, char **flags) {
    for (int i = 0; flags[i]; i++) {
        if (mx_has_output_format_flag(flags))
            s->has_output_format_flag = true;
        if (isatty(1))
            s->is_atty = true;
        if (flags[i][0] == 'r')
            s->reverse = true;
        if (flags[i][0] == 'n')
            s->n = true;
        if (flags[i][0] == 'h')
            s->format_size = true;
        if (flags[i][0] == '@')
            s->print_xattr = true;
        if (flags[i][0] == 'x')
            s->print_xcols = true;
        if (flags[i][0] == 'T')
            s->full_time = true;
        if (flags[i][0] == 'p') {
            s->append_slash = true;
            s->append_type_sign = false;
        }
        find_flags_2(s, flags[i][0]);
    }
}

static t_sorting_enum setup_sorting(char **flags) {
    int len = mx_strarr_len(flags) - 1;
    t_sorting_enum mode = names;

    for (; len >= 0; len--) {
        if (flags[len][0] == 'f') {
            mode = unsorted;
            break;
        }
        else if (flags[len][0] == 'S')
            mode = size;
        else if (flags[len][0] == 't' && mode != size) {
            if (mx_search_strarr(flags, "c"))
                mode = chg_time;
            else if (mx_search_strarr(flags, "u"))
                mode = acc_time;
            else if (mx_search_strarr(flags, "U"))
                mode = crt_time;
            else
                mode = mod_time;
        }
    }
    return mode;
}

static t_mode_enum process_mode(char flag) {
    t_mode_enum mode;

    if (flag == 'C' || flag == 'x')
        mode = columns;
    else if (flag == 'l' || flag == 'g' || flag == 'o' || flag == 'n')
        mode = table;
    else if (flag == 'm')
        mode = commas;
    else
        mode = line_break;
    return mode;
}

static t_mode_enum setup_mode(char **flags) {
    int len = mx_strarr_len(flags) - 1;
    int fish = 0;
    t_mode_enum mode = columns;

    for (; len >= 0; len--) {
        for (int i = 0; i < mx_strlen(MODE_FLAGS); i++) {
            if (mx_get_char_index(flags[len], MODE_FLAGS[i]) == 0) {
                mode = process_mode(MODE_FLAGS[i]);
                if (mode == columns && find_flag(flags, 'm'))
                    mode = commas;
                fish = 1;
                break;
            }
        }
        if (fish)
            break;
    }
    return mode;
}

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));

    if (flags) {
        setup->mode = setup_mode(flags);
        setup->sorting = setup_sorting(flags);
        find_flags(setup, flags);
    }
    return setup;
}

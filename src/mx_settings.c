#include "uls.h"

static t_mode_enum setup_mode(char **flags);
static t_mode_enum process_mode(char flag);
static t_sorting_enum setup_sorting(t_settings *s, char **flags);
static void find_flags(t_settings *s, char **flags);
static bool find_flag(char **flags, char f);

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));

    if (flags) {
        setup->mode = setup_mode(flags);
        setup->sorting = setup_sorting(setup, flags);
        find_flags(setup, flags);
    }
    return setup;
}

static void find_flags(t_settings *s, char **flags) {
    for (int i = 0; flags[i]; i++) {
        if (flags[i][0] == 'r')
            s->reverse = true;
        else if (flags[i][0] == 'h')
            s->format_size = true;
        else if (flags[i][0] == '@')
            s->print_xattr = true;
        else if (flags[i][0] == 'x')
            s->print_xcols = true;
        else if (flags[i][0] == 'T')
            s->full_time = true;
        else if (flags[i][0] == 'p')
            s->print_slash = true;
        else if (flags[i][0] == 'o')
            s->omit_group = true;
        else if (flags[i][0] == 'g')
            s->omit_owner = true;
        else if (flags[i][0] == 'G')
            s->colored = true;
        else if (flags[i][0] == 'i')
            s->print_inode = true;
        else if (flags[i][0] == 'p')
            s->append_slash = true;
        else if (flags[i][0] == 'F')
            s->append_type_sign = true;
        else if (flags[i][0] == 'R')
            s->R = true;
        else if (flags[i][0] == 'A')
            s->A = true;
        else if (flags[i][0] == 'a' || flags[i][0] == 'f')
            s->a = true;
    }
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

static t_mode_enum process_mode(char flag) {
    t_mode_enum mode;

    if (flag == 'C' || flag == 'x')
        mode = columns;
    else if (flag == 'l')
        mode = table;
    else if (flag == 'm')
        mode = commas;
    else
        mode = line_break;
    return mode;
}

static t_sorting_enum setup_sorting(t_settings *s, char **flags) {
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
            if (mx_search_strarr(flags, "c")) {
                mode = chg_time;
                s->time = chg;
            }
            else if (mx_search_strarr(flags, "u")) {
                mode = acc_time;
                s->time = acc;
            }
            else if (mx_search_strarr(flags, "U")) {
                mode = crt_time;
                s->time = crt;
            }
            else {
                mode = mod_time;
                s->time = mod; //this line can optionally be removed but i left it for consistency, s->time = mod (0) by default
            }
        }
    }
    return mode;
}

static bool find_flag(char **flags, char f) {
    for (int i = 0; flags[i]; i++)
        if (flags[i][0] == f)
            return true;
    return false;
}

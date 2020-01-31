#include "uls.h"

static t_mode_enum setup_mode(char **flags);
static t_mode_enum process_mode(char flag);
static t_sorting_enum setup_sorting(char **flags);
static t_sorting_enum process_sorting(char flag);
static void find_flags(t_settings *s, char **flags);
static bool find_flag(char **flags, char f);

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));

    if (flags) {
        setup->mode = setup_mode(flags);
        setup->sorting = setup_sorting(flags);
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

static t_sorting_enum setup_sorting(char **flags) {
    int len = mx_strarr_len(flags) - 1;
    int fish = 0;
    t_sorting_enum mode = names;

    for (; len >= 0; len--) {
        for (int i = 0; i < mx_strlen(SORTING_FLAGS); i++) {
            if (mx_get_char_index(flags[len], SORTING_FLAGS[i]) == 0 &&
                !fish) {
                mode = process_sorting(SORTING_FLAGS[i]);
                fish = 1;
                break;
            }
        }
    }
    return mode;
}

static t_sorting_enum process_sorting(char flag) {
    t_sorting_enum mode = names;

    if (flag == 'S')
        mode = size;
    else if (flag == 't')
        mode = mod_time;
    else if (flag == 'f')
        mode = unsorted;

    return mode;
}

static bool find_flag(char **flags, char f) {
    for (int i = 0; flags[i]; i++)
        if (flags[i][0] == f)
            return true;
    return false;
}

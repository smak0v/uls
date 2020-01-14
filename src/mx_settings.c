#include "uls.h"

static int setup_mode(char **flags);
static t_mode_enum process_mode(char flag);
static int setup_sorting(char **flags);
static t_sorting_enum process_sorting(char flag);

t_settings *mx_setup(char **flags) {
    t_settings *setup = malloc(sizeof(t_settings));

    if (*flags == NULL) {
        setup->mode = columns;
        setup->sorting = names;
        setup->data = 0;
        setup->reverse = 0;
        setup->format_size = 0;
        setup->print_xattr = 0;
        setup->print_acl = 0;
    }
    else {
        setup->mode = setup_mode(flags);
        setup->sorting = setup_sorting(flags);
        // setup->data = setup_data(flags);
        setup->reverse = mx_check_reverse(flags);
        // setup->format_size = setup_format_size(flags); TODO (Yulia) -h
        // setup->print_xattr = setup_print_xattr(flags); TODO (Yulia) -@
        // setup->print_acl = setup_print_acl(flags); TODO (Yulia) -e
        setup->format_size = 0;
        setup->print_xattr = 0;
        setup->print_acl = 0;
    }
    return setup;
}

static int setup_mode(char **flags) {
    int len = mx_strarr_len(flags) - 1;
    int fish = 0;
    t_mode_enum mode = columns;

    for (; len >= 0; len--) {
        for (int i = 0; i < mx_strlen(MODE_FLAGS); i++) {
            if (mx_get_char_index(flags[len], MODE_FLAGS[i]) == 0) {
                mode = process_mode(MODE_FLAGS[i]);
                fish = 1;
                break;
            }
        }
        if (fish)
            break;
    }
    return (int)mode;
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

static int setup_sorting(char **flags) {
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
    return (int)mode;
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

#include "uls.h"

static int setup_mode(char **flags);
static t_mode_enum process_mode(char flag);
static int setup_sorting(char **flags);
static t_sorting_enum process_sorting(char flag);
static t_data_enum *setup_data(t_settings *setup, char **flags);

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));

    if (flags) {    
        setup->mode = setup_mode(flags);
        setup->sorting = setup_sorting(flags);
        setup->data = setup_data(setup, flags);
        setup->reverse = mx_search_arr(setup, r);
        setup->format_size = mx_search_arr(setup, h);
        setup->print_xattr = mx_search_arr(setup, xattrs);
        setup->print_xcols = mx_search_arr(setup, x);
        setup->full_time = mx_search_arr(setup, T);
        setup->omit_group = mx_search_arr(setup, o);
        setup->colored = mx_search_arr(setup, G);
        setup->omit_owner = mx_search_arr(setup, g);
        setup->print_inode = mx_search_arr(setup, i);
        setup->append_slash = mx_search_arr(setup, p);
        setup->append_type_sign = mx_search_arr(setup, F);
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

static t_data_enum analyser_data(char flag) {
    t_data_enum mode = def;

    if (flag == 'R')
        mode = R;
    else if (flag == 'a' || flag == 'f')
        mode = a;
    else if (flag == 'A')
        mode = A;
    else
        mode = l;

    return mode;
}

static t_data_enum *process_data(char **set, int data_len) {
    t_data_enum *data = malloc(sizeof(t_data_enum) * data_len);

    for (int i = 0; i < data_len; i++) {
        data[i] = analyser_data(set[i][0]);
    }

    return data;
}

static t_data_enum *setup_data(t_settings *setup, char **flags) {
    int data_len = 0;
    char **set = NULL;
    t_data_enum *arr = NULL;

    data_len = mx_count_unique(flags, DATA_FLAGS);
    setup->data_len = data_len;

    if (data_len) {
        set = mx_create_custom_set(flags, DATA_FLAGS);
        arr = process_data(set, data_len);
        mx_del_strarr(&set);
    }

    return arr;
}

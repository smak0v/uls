#include "uls.h"

static bool find_flag(char **flags, char flag, int position, int arr_len) {
    if (position - 1 >= 0)
        if (flags[position - 1][0] == flag)
            return true;
    if (position + 1 < arr_len)
        if (flags[position + 1][0] == flag)
            return true;
    return false;
}

static void setup_sorting(char **flags, t_sorting_enum *sorting_mode) {
    int len = mx_strarr_len(flags) - 1;

    for (; len >= 0; --len) {
        if (flags[len][0] == 'f') {
            *sorting_mode = unsorted;
            break;
        }
        else if (flags[len][0] == 'S')
            *sorting_mode = size;
        else if ((flags[len][0] == 't') && (*sorting_mode != size))
            mx_find_sorting_combination_flags(sorting_mode, flags);
    }
}

static t_mode_enum process_mode(char flag) {
    t_mode_enum mode = columns;

    if (flag == 'C')
        mode = columns;
    else if (flag == 'x')
        mode = x_columns;
    else if (flag == 'l' || flag == 'g' || flag == 'o' || flag == 'n')
        mode = table;
    else if (flag == 'm')
        mode = commas;
    else
        mode = line_break;
    return mode;
}

static void setup_mode(char **flags, t_mode_enum *output_mode) {
    int len = mx_strarr_len(flags) - 1;
    int fish = 0;

    for (; len >= 0; --len) {
        for (int i = 0; i < mx_strlen(MODE_FLAGS); ++i) {
            if (mx_get_char_index(flags[len], MODE_FLAGS[i]) == 0) {
                *output_mode = process_mode(MODE_FLAGS[i]);
                if (*output_mode == columns
                    && find_flag(flags, 'm', len, mx_strarr_len(flags) - 1))
                    *output_mode = commas;
                fish = 1;
                break;
            }
        }
        if (fish)
            break;
    }
}

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));
    t_sorting_enum sorting_mode = names;
    t_mode_enum output_mode = columns;

    setup->is_first = true;
    setup->is_atty = isatty(1);
    if (flags) {
        setup_mode(flags, &output_mode);
        setup_sorting(flags, &sorting_mode);
        setup->mode = output_mode;
        setup->sorting = sorting_mode;
        if (mx_has_output_format_flag(flags))
            setup->has_output_format_flag = true;
        mx_find_flags(setup, flags);
    }
    return setup;
}

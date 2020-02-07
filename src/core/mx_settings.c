#include "uls.h"

static bool find_flag(char **flags, char flag, int position, int arr_len) {
    if (position == 0 || position == arr_len + 1)
        return false;
    if (flags[position - 1][0] == flag || flags[position + 1][0] == flag)
        return true;
    return false;
}

static void setup_sorting(char **flags, int arr_len,
                          t_sorting_enum *sorting_mode) {
    for (; arr_len >= 0; arr_len--) {
        if (flags[arr_len][0] == 'f') {
            *sorting_mode = unsorted;
            break ;
        }
        else if (flags[arr_len][0] == 'S')
            *sorting_mode = size;
        else if ((flags[arr_len][0] == 't') && (*sorting_mode != size)) {
            if (mx_search_strarr(flags, "c"))
                *sorting_mode = chg_time;
            else if (mx_search_strarr(flags, "u"))
                *sorting_mode = acc_time;
            else if (mx_search_strarr(flags, "U"))
                *sorting_mode = crt_time;
            else
                *sorting_mode = mod_time;
        }
    }
}

static t_mode_enum process_mode(char flag) {
    t_mode_enum mode = columns;

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

static t_mode_enum setup_mode(char **flags, int arr_len,
                              t_mode_enum *output_mode) {
    int len = arr_len;
    int fish = 0;

    for (; len >= 0; --len) {
        for (int i = 0; i < mx_strlen(MODE_FLAGS); ++i) {
            if (mx_get_char_index(flags[len], MODE_FLAGS[i]) == 0) {
                *output_mode = process_mode(MODE_FLAGS[i]);
                if (*output_mode == columns
                    && find_flag(flags, 'm', len, arr_len))
                    *output_mode = commas;
                fish = 1;
                break ;
            }
        }
        if (fish)
            break ;
    }
    return *output_mode;
}

t_settings *mx_setup(char **flags) {
    t_settings *setup = mx_memalloc(sizeof(t_settings));
    t_sorting_enum sorting_mode = names;
    t_mode_enum output_mode = columns;
    int arr_len = 0;

    setup->is_first = true;
    setup->is_atty = isatty(1);
    if (flags) {
        arr_len = mx_strarr_len(flags) - 1;
        setup_mode(flags, arr_len, &output_mode);
        setup_sorting(flags, arr_len, &sorting_mode);
        setup->mode = output_mode;
        setup->sorting = sorting_mode;
        if (mx_has_output_format_flag(flags))
            setup->has_output_format_flag = true;
        mx_find_flags(setup, flags);
    }
    return setup;
}

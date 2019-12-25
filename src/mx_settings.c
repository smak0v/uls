#include "uls.h"

static t_mode_enum process_mode(char flag) {
    t_mode_enum mode;

    if (flag == 'C' || flag == 'x') {
        mode = columns;
    }
    else if (flag == 'l') {
        mode = table;
    }
    else if (flag == 'm') {
        mode = commas;
    }
    else { // flag = '1'
        mode = line_break;
    }

    return mode;
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
        if (fish) {
            break;
        }
    }
    return (int) mode;
}

// static int setup_data(flags);

t_settings *mx_setup(char **flags) {
    t_settings *setup = malloc(sizeof(t_settings));

    if (*flags == NULL) {
        setup->mode = 0;
        setup->sorting = 0;
        setup->data = 0;
    }
    else {
        setup->mode = setup_mode(flags);
        // setup->sorting = setup_sorting(flags);
        // setup->data = setup_data(flags);
    }
    return setup;
}

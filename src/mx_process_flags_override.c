#include "uls.h"

static void del_extra_flags(char **flags, char **o_flags, int index, int n) {
    mx_printstr("4\n");
    int new_len = mx_get_arr_length(flags) - n;
    char **new_flags = malloc(sizeof(char *) * new_len);
    int k = 0;

    for (int i = 0; flags[i]; i++) {
        for (int j = 0; o_flags[j]; j++) {
            if (mx_strcmp(flags[i], o_flags[j]) != 0 || i == index) {
                new_flags[k] = mx_strdup(flags[i]);
                k++;
                break;
            }
        }
    }

    mx_del_strarr(&flags);
    *flags = *new_flags;
    mx_printstr("5\n");
}

static void process_flags(char **flags, char **o_flags) {
    mx_printstr("2\n");
    int len = mx_get_arr_length(flags);
    int index = -1;
    int counter = -1;

    for (int i = len - 1; i >= 0; i++) {
        for (int j = 0; o_flags[j]; j++) {
            if (!mx_strcmp(flags[i], o_flags[j])) {
                counter++;
                if (index == -1) {
                    index = i;
                }
                
            }
        }
    }

    if (index != -1 && counter > 0) {
        del_extra_flags(flags, o_flags, index, counter);
    }
    mx_printstr("3\n");
}

static void process_mode_flags(char **flags) {
    char *mode_flags[6] = {"C", "x", "l", "1", "m", NULL};
    mx_printstr("1\n");
    process_flags(flags, mode_flags);
}

void mx_process_flags_override(char **flags) {
    process_mode_flags(flags);
    // process sorting flags(flags);
    // process data flags(flags);
}

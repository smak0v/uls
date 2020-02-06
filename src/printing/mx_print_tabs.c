#include "uls.h"

static void print(int max_len, int prev_len, t_settings *settings) {
    int spaces_count = 0;
    int tabs_count = 0;

    if (!(max_len % 8))
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8)
            ++spaces_count;
    }
    tabs_count = ((spaces_count - prev_len) / 8) + 1;
    if (!(prev_len % 8))
        --tabs_count;
    if (!((prev_len + 1) % 8)
        && (settings->append_slash || settings->append_type_sign))
        --tabs_count;
    while (tabs_count--)
        mx_printchar('\t');
}

void mx_print_tabs(t_settings *settings, t_columns_info *info, t_data *prev) {
    if (settings->print_inode)
        print(info->max_len,
              mx_strlen(prev->filename) + info->max->inodes + 1, settings);
    else
        print(info->max_len , mx_strlen(prev->filename), settings);
}

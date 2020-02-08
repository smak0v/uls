#include "uls.h"

static void fill_info_cols(t_settings *settings, t_columns_info *info) {
    ushort width = mx_get_terminal_width(settings);

    if (!settings->colored)
        info->cols = width / ((8 - (info->max_len % 8)) + info->max_len);
    else
        info->cols = width / (info->max_len + 1);
    if (!info->cols)
        ++info->cols;
}

t_columns_info *mx_get_columns_info(t_list **list, t_settings *settings,
                                    t_max_len *max) {
    t_columns_info *info = (t_columns_info *)malloc(sizeof(t_columns_info));
    int tmp_max_len = max->filenames;

    if (settings->print_inode)
        info->max_len = tmp_max_len + max->inodes + 1;
    else
        info->max_len = tmp_max_len;
    info->list_size = mx_list_size(*list);
    fill_info_cols(settings, info);
    info->rows = info->list_size / info->cols;
    info->max = max;
    info->i = 0;
    info->j = 0;
    if (!info->rows || info->list_size % info->cols)
        ++info->rows;
    return info;
}

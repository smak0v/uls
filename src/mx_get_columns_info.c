#include "uls.h"

t_columns_info *mx_get_columns_info(t_list **list) {
    t_columns_info *info = (t_columns_info *)malloc(sizeof(t_columns_info));
    ushort width = mx_get_terminal_width();

    info->max_len = mx_get_max_filename_length(list);
    info->list_size = mx_list_size(*list);
    info->cols = width / ((8 - (info->max_len % 8)) + info->max_len);
    info->rows = info->list_size / info->cols;
    info->i = 0;
    info->j = 0;
    if (!info->rows || info->list_size % info->cols)
        info->rows++;
    return info;
}

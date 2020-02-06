#include "uls.h"

static void print_row(t_list *node1, t_columns_info *info, bool is_first,
t_settings *settings) {
    char *prev = NULL;
    t_data *data = NULL;

    for (t_list *node2 = node1; node2; node2 = node2->next) {
        data = (t_data *)node2->data;
        if (!is_first && !settings->colored)
            mx_print_tabs(settings, info, prev);
        else if (!is_first)
            mx_print_spaces(info->max_len - mx_strlen(prev) + 1);
        mx_print_inode(settings, data->inode, info->max);
        mx_print_filename(data, settings);
        ++info->j;
        is_first = false;
        prev = data->filename;
        if (!(info->j % info->cols)) {
            mx_printchar('\n');
            info->j = 0;
            is_first = true;
        }
    }
}

static void print_x_columns(t_list **list, t_settings *settings,
t_max_len *max) {
    t_columns_info *info = mx_get_columns_info(list, settings, max);
    bool is_first = true;

    for (t_list *node1 = *list; node1; node1 = node1->next) {
        ++info->i;
        is_first = true;
        print_row(node1, info, is_first, settings);
        info->j = 0;
        if ((mx_list_size(node1) % info->cols))
            mx_printchar('\n');
        if (info->i % info->cols)
            break;
    }
    free(info);
    info = NULL;
}

void mx_print_x_columns(t_list **list, t_settings *settings, bool many_lists,
                        bool *is_first) {
    t_list *node = *list;
    t_list *next = ((t_list *)node->data)->next;
    t_max_len *max_len = mx_get_max_len_struct(node, settings);

    if (many_lists)
        mx_print_dir(((t_data *)((t_list *)node->data)->data)->filename,
                     is_first, settings);
    print_x_columns(&next, settings, max_len);
    free(max_len);
    max_len = NULL;
}

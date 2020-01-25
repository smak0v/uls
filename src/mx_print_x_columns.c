#include "uls.h"

static void output_with_paths(t_list **list, t_settings *settings);
static void print_x_columns(t_list **list, t_settings *settings,
t_max_len *max);
static void print_row(t_list *node1, t_columns_info *info, bool is_first,
t_settings *settings);
static void print_tabs(int max_len, int prev_len);

void mx_print_x_columns(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_max_len *max_len = mx_get_max_len_struct(node);
    t_list *inner_list = ((t_list *)(node->data))->next;

    if (mx_list_size(*list) == 1 && settings->not_found) {
        print_x_columns(&inner_list, settings, max_len);
        free(max_len);
        max_len = NULL;
    }
    else
        output_with_paths(list, settings);
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_list = NULL;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_list = ((t_list *)(node->data))->next;
        print_x_columns(&inner_list, settings, max_len);
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print_x_columns(t_list **list, t_settings *settings,
t_max_len *max) {
    t_columns_info *info = mx_get_columns_info(list, settings, max);
    bool is_first = true;

    for (t_list *node1 = *list; node1; node1 = node1->next) {
        info->i++;
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

static void print_row(t_list *node1, t_columns_info *info, bool is_first,
t_settings *settings) {
    char *prev = NULL;
    t_data *data = NULL;

    for (t_list *node2 = node1; node2; node2 = node2->next) {
        data = (t_data *)node2->data;
        if (!is_first)
            print_tabs(info->max_len, mx_strlen(prev));
        mx_print_inode(settings, data->inode, info->max);
        mx_print_filename(data, settings);
        info->j++;
        is_first = false;
        prev = data->filename;
        if (!(info->j % info->cols)) {
            mx_printchar('\n');
            info->j = 0;
            is_first = true;
        }
    }
}

static void print_tabs(int max_len, int prev_len) {
    int spaces_count = 0;
    int tabs_count = 0;

    if (!(max_len % 8))
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8)
            spaces_count++;
    }
    tabs_count = (spaces_count - prev_len) / 8;
    if (!(prev_len % 8))
        tabs_count--;
    while (tabs_count--)
        mx_printchar('\t');
    mx_printchar('\t');
}

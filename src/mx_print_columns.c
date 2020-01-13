#include "uls.h"

static void output_with_paths(t_list **list);
static void print_columns(t_list **list);
static int get_spaces(int max_len);
static t_columns_info *get_columns_info(t_list **list);

void mx_print_columns(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_list = ((t_list *)(node->data))->next;

    if (mx_list_size(*list) == 1 && settings->not_found)
        print_columns(&inner_list);
    else
        output_with_paths(list);
}

static void output_with_paths(t_list **list) {
    t_list *node = *list;
    t_list *inner_list = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_list = ((t_list *)(node->data))->next;
        print_columns(&inner_list);
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print_columns(t_list **list) {
    t_columns_info *info = get_columns_info(list);
    char *file = NULL;
    
    for (t_list *node1 = *list; node1; node1 = node1->next) {
        info->i++;
        for (t_list *node2 = node1; node2; node2 = node2->next) {
            if (!(info->j % info->rows)) {
                file = ((t_data *)(node2->data))->filename;
                mx_printstr(file);
                mx_print_spaces(get_spaces(info->max_len) - mx_strlen(file));
            }
            info->j++;
        }
        info->j = 0;
        mx_printchar('\n');
        if (!(info->i % info->rows))
            break;
    }
    free(info);
    info = NULL;
}

static t_columns_info *get_columns_info(t_list **list) {
    t_columns_info *info = (t_columns_info *)malloc(sizeof(t_columns_info));
    unsigned short width = mx_get_terminal_width();

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

static int get_spaces(int max_len) {
    int spaces_count = 0;

    if (!(max_len % 8))
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8)
            spaces_count++;
    }
    return spaces_count;
}

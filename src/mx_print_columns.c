#include "uls.h"

static void output_with_paths(t_list **list, t_settings *settings);
static void print_columns(t_list **list, t_settings *settings);
static void print_row(t_list *node1, t_columns_info *info, bool is_first,
t_settings *settings);
static int get_spaces(int max_len);

void mx_print_columns(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_list = ((t_list *)(node->data))->next;

    if (mx_list_size(*list) == 1 && settings->not_found)
        print_columns(&inner_list, settings);
    else
        output_with_paths(list, settings);
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_list = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_list = ((t_list *)(node->data))->next;
        print_columns(&inner_list, settings);
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print_columns(t_list **list, t_settings *settings) {
    t_columns_info *info = mx_get_columns_info(list);
    bool is_first = true;

    for (t_list *node1 = *list; node1; node1 = node1->next) {
        info->i++;
        is_first = true;
        print_row(node1, info, is_first, settings);
        info->j = 0;
        if ((mx_list_size(node1) % info->rows + 1))
            mx_printchar('\n');
        if (!(info->i % info->rows))
            break;
    }
    free(info);
    info = NULL;
}

static void print_row(t_list *node1, t_columns_info *info, bool is_first,
t_settings *settings) {
    char *prev = NULL;

    for (t_list *node2 = node1; node2; node2 = node2->next) {
        if (!(info->j % info->rows)) {
            if (!is_first)
                mx_print_spaces(get_spaces(info->max_len) - mx_strlen(prev));
            mx_print_filename((t_data *)node2->data, settings);
            is_first = false;
            prev = ((t_data *)(node2->data))->filename;
        }
        info->j++;
    }
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

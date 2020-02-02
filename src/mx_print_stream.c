#include "uls.h"

static void print(t_list **node, int *len, t_max_len *max_len,
                  t_settings *settings) {
    char *file = ((t_data *)((*node)->data))->filename;
    ushort width = mx_get_terminal_width(settings);

    if (settings->print_inode) {
        if (*len + mx_strlen(file) + 3 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        *len +=  max_len->inodes + mx_strlen(file) + 3;
    } else {
        if (*len + mx_strlen(file) + 2 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        *len += mx_strlen(file) + 2;
    }
    mx_print_inode(settings, ((t_data *)(*node)->data)->inode, max_len);
    mx_print_filename((t_data *)(*node)->data, settings);
    (*node)->next ? mx_printstr(", ") : (void)0;
    *node = (*node)->next;
}

static void reset_values(int *len, t_max_len **max_len) {
    *len = 0;
    free(*max_len);
    *max_len = NULL;
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    int len = 0;
    bool is_first = true;

    while (node) {
        max_len = mx_get_max_len_struct(node, settings);
        mx_print_dir(((t_data *)((t_list *)node->data)->data)->filename,
                     &is_first, settings);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node)
            print(&inner_node, &len, max_len, settings);
        !mx_strcmp(((t_data *)((t_list *)node->data)->data)->filename, FILES) ?
                   mx_printstr(", \n") : mx_printchar('\n');
        reset_values(&len, &max_len);
        node = node->next;
        node ? mx_printchar('\n') : (void)0;
    }
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    int len = 0;

    while (node) {
        max_len = mx_get_max_len_struct(node, settings);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node)
            print(&inner_node, &len, max_len, settings);
        reset_values(&len, &max_len);
        node = node->next;
        !node ? mx_printchar('\n') : (void)0;
    }
}

void mx_print_stream(t_list **list, t_settings *settings) {
    if ((list && *list && (*list)->next) || settings->not_found)
        output_with_paths(list, settings);
    else
        simple_output(list, settings);
}

#include "uls.h"

static void simple_output(t_list **list, t_settings *settings);
static void output_with_paths(t_list **list, t_settings *settings);
static void print(t_list *node, int *len, t_max_len *max_len,
t_settings *settings);

void mx_print_stream(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && settings->not_found)
        simple_output(list, settings);
    else
        output_with_paths(list, settings);
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    int len = 0;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, max_len, settings);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
    }
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    int len = 0;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, max_len, settings);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print(t_list *node, int *len, t_max_len *max_len,
t_settings *settings) {
    char *file = ((t_data *)(node->data))->filename;
    ushort width = mx_get_terminal_width();

    if (settings->print_inode) {
        if (*len + max_len->inodes + 1 + mx_strlen(file) + 2 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        else
            *len += max_len->inodes + 1 + mx_strlen(file) + 2;
    } else {
        if (*len + mx_strlen(file) + 2 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        else
            *len += mx_strlen(file) + 2;
    }
    mx_print_inode(settings, ((t_data *)node->data)->inode, max_len);
    mx_print_filename((t_data *)node->data, settings);
    node->next ? mx_printstr(", ") : mx_printchar('\n');
}

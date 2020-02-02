#include "uls.h"

static void simple_output(t_list **list, t_settings *settings);
static void output_with_paths(t_list **list, t_settings *settings);
static void print(t_list *node, int *len, t_max_len *max_len,
t_settings *settings);
static void reset_values(int *len, t_max_len **max_len);

void mx_print_stream(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && !settings->not_found)
        simple_output(list, settings);
    else
        output_with_paths(list, settings);
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    int len = 0;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, max_len, settings);
            inner_node = inner_node->next;
        }
        reset_values(&len, &max_len);
        node = node->next;
        !node ? mx_printchar('\n') : (void)0;
    }
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    int len = 0;
    char *tmp = NULL;
    bool is_first = true;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        tmp = ((t_data *)((t_list *)node->data)->data)->filename;
        mx_strcmp(tmp, FILES) ? mx_print_dir(tmp, is_first, settings) : (void)0;
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, max_len, settings);
            inner_node = inner_node->next;
        }
        is_first = false;
        !mx_strcmp(tmp, FILES) ? mx_printstr(", \n") : mx_printchar('\n');
        reset_values(&len, &max_len);
        node = node->next;
        node ? mx_printchar('\n') : (void)0;
    }
}

static void print(t_list *node, int *len, t_max_len *max_len,
t_settings *settings) {
    char *file = ((t_data *)(node->data))->filename;
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
    mx_print_inode(settings, ((t_data *)node->data)->inode, max_len);
    mx_print_filename((t_data *)node->data, settings);
    node->next ? mx_printstr(", ") : (void)0;
}

static void reset_values(int *len, t_max_len **max_len) {
    *len = 0;
    free(*max_len);
    *max_len = NULL;
}

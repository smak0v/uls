#include "uls.h"

static void simple_output(t_list **list, t_settings *settings);
static void output_with_paths(t_list **list, t_settings *settings);
static void print(t_list *node, t_settings *settings, t_max_len *max_len);

void mx_print_force(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && !settings->not_found)
        simple_output(list, settings);
    else
        output_with_paths(list, settings);
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, settings, max_len);
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
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr_endl(":");
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, settings, max_len);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print(t_list *node, t_settings *settings, t_max_len *max_len) {
    t_data *data = (t_data *)node->data;

    mx_print_inode(settings, data->inode, max_len);
    mx_print_filename(data, settings);
    mx_printchar('\n');
}

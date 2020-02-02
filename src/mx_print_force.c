#include "uls.h"

static void print(t_list *node, t_settings *settings, t_max_len *max_len) {
    t_data *data = (t_data *)node->data;

    mx_print_inode(settings, data->inode, max_len);
    mx_print_filename(data, settings);
    mx_printchar('\n');
}

static void output_with_paths(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    char *tmp = NULL;
    bool is_first = true;

    while (node) {
        max_len = mx_get_max_len_struct(node, settings);
        tmp = ((t_data *)((t_list *)node->data)->data)->filename;
        mx_print_dir(tmp, &is_first, settings);
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, settings, max_len);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        node ? mx_printchar('\n') : (void)0;
    }
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node, settings);
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

void mx_print_force(t_list **list, t_settings *settings) {
    if ((list && *list && (*list)->next) || settings->not_found)
        output_with_paths(list, settings);
    else
        simple_output(list, settings);       
}

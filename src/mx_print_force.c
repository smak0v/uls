#include "uls.h"

static void simple_output(t_list **list);
static void output_with_paths(t_list **list);

void mx_print_force(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && settings->not_found)
        simple_output(list);
    else
        output_with_paths(list);
}

static void simple_output(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            mx_printstr_endl(((t_data *)inner_node->data)->filename);
            inner_node = inner_node->next;
        }
        node = node->next;
    }
}

static void output_with_paths(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            mx_printstr_endl(((t_data *)inner_node->data)->filename);
            inner_node = inner_node->next;
        }
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

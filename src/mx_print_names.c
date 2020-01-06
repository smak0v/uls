#include "uls.h"

static void simple_output(t_list **list, char *delim);
static void output_with_paths(t_list **list, char *delim);

void mx_print_names(t_list **list, char *delim, int not_found) {
     if (mx_list_size(*list) == 1  && not_found)
        simple_output(list, delim);
    else
        output_with_paths(list, delim);
}

static void simple_output(t_list **list, char *delim) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            mx_printstr(((t_data *)inner_node->data)->filename);
            inner_node->next ? mx_printstr(delim) : mx_printchar('\n');
            inner_node = inner_node->next;
        }
        node = node->next;
    }
}

static void output_with_paths(t_list **list, char *delim) {
    t_list *node = *list;
    t_list *inner_node = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            mx_printstr(((t_data *)inner_node->data)->filename);
            inner_node->next ? mx_printstr(delim) : mx_printchar('\n');
            inner_node = inner_node->next;
        }
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

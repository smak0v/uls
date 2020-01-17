#include "uls.h"

static void simple_output(t_list **list);
static void output_with_paths(t_list **list);
static void print(t_list *node, int *len, unsigned short width);

void mx_print_stream(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && settings->not_found)
        simple_output(list);
    else
        output_with_paths(list);
}

static void simple_output(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    unsigned short width = mx_get_terminal_width();
    int len = 0;

    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, width);
            inner_node = inner_node->next;
        }
        node = node->next;
    }
}

static void output_with_paths(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    unsigned short width = mx_get_terminal_width();
    int len = 0;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            print(inner_node, &len, width);
            inner_node = inner_node->next;
        }
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print(t_list *node, int *len, unsigned short width) {
    char *file = ((t_data *)(node->data))->filename;

    if (*len + mx_strlen(file) + 2 >= width) {
        mx_printchar('\n');
        *len = 0;
    }
    mx_printstr(file);
    node->next ? mx_printstr(", ") : mx_printchar('\n');
    *len += mx_strlen(file) + 2;
}

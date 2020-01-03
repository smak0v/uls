#include "uls.h"

static void print_names(t_list **list, char *delim) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;

    while (node) {
        inner_node = node->data;
        if (mx_strcmp((char *) inner_node->data, ".")) {
            mx_printstr((char *) inner_node->data);
            mx_printstr(":\n");
        }
        inner_node = inner_node->next;
        while (inner_node) {
            data = (t_data *) inner_node->data;
            mx_printstr(data->filename);
            if (inner_node->next) {
                mx_printstr(delim);
            }
            else if (node->next) {
                mx_printchar('\n');
            }
            inner_node = inner_node->next;
        }
        mx_printchar('\n');
        node = node->next;
    }
}

void mx_process_output(t_list **data, t_settings *settings) {
    t_mode_enum mode;

    mx_sort_by_name(data);
    if ((int)(mode = columns) == settings->mode)
        return;
    else if ((int)(mode = table) == settings->mode)
        mx_print_l(data);
    else if ((int)(mode = commas) == settings->mode)
        print_names(data, ", ");
    else
        print_names(data, "\n");
}

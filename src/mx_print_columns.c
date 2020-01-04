#include "uls.h"

static void simple_output(t_list **list, bool is_atty);
static void output_with_paths(t_list **list, bool is_atty);
static void print_columns(t_list **list);

void mx_print_columns(t_list **list) {
    bool is_atty = isatty(1);

    if (mx_list_size(*list) == 1)
        simple_output(list, !is_atty);
    else
        output_with_paths(list, !is_atty);
}

static void simple_output(t_list **list, bool is_atty) {
    t_list *node = *list;
    t_list *inner_list = ((t_list *)(node->data))->next;

    if (is_atty)
        mx_print_names(&inner_list, "\n");
    else
        print_columns(&inner_list);
}

static void output_with_paths(t_list **list, bool is_atty) {
    t_list *node = *list;
    t_list *inner_list = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_list = ((t_list *)(node->data))->next;
        if (is_atty)
            mx_print_names(&inner_list, "\n");
        else
            print_columns(&inner_list);
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print_columns(t_list **list) {
    // int max_len = mx_get_max_filename_length(list);
    // int cols_count = mx_get_terminal_width() / ((8 - (max_len % 8)) + max_len);
    // int count_per_column = (mx_list_size(*list) / cols_count) + 1;
    // int i = 0;

    // mx_printint_endl(cols_count);
    // mx_printint_endl(count_per_column);
    // for (t_list *node1 = *list; node1; node1 = node1->next) {
    //     i = 0;
    //     for (t_list *node2 = node1; node2; node2 = node2->next) {
    //         if (i % cols_count != 0)
    //             break;
    //         mx_printstr(((t_data *)(node2->data))->filename);
    //         mx_print_spaces(max_len - mx_strlen(((t_data *)(node2->data))->filename));
    //         //else mx_printchar('\n');
    //         i++;
    //     }
    // }
    list = NULL;
}

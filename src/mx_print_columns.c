#include "uls.h"

static void simple_output(t_list **list);
static void output_with_paths(t_list **list);
static void print_columns(t_list **list);
static int get_spaces(int max_len);

void mx_print_columns(t_list **list, int not_found) {
    if (mx_list_size(*list) == 1 && not_found)
        simple_output(list);
    else
        output_with_paths(list);
}

static void simple_output(t_list **list) {
    t_list *node = *list;
    t_list *inner_list = ((t_list *)(node->data))->next;

    print_columns(&inner_list);
}

static void output_with_paths(t_list **list) {
    t_list *node = *list;
    t_list *inner_list = NULL;

    while (node) {
        mx_printstr(((t_list *)(node->data))->data);
        mx_printstr(":\n");
        inner_list = ((t_list *)(node->data))->next;
        print_columns(&inner_list);
        node = node->next;
        if (node)
            mx_printchar('\n');
    }
}

static void print_columns(t_list **list) {
    int max_len = mx_get_max_filename_length(list);
    int cols_count = mx_get_terminal_width() / ((8 - (max_len % 8)) + max_len);
    int count_per_column = mx_list_size(*list) / cols_count;
    int i = 0;
    int j = 0;
    
    if (!count_per_column)
        count_per_column++;
    for (t_list *node1 = *list; node1; node1 = node1->next) {
        i++;
        for (t_list *node2 = node1; node2; node2 = node2->next) {
            if (j % count_per_column == 0) {
                mx_printstr(((t_data *)(node2->data))->filename);
                mx_print_spaces(get_spaces(max_len) - mx_strlen(((t_data *)(node2->data))->filename));
            }
            j++;
        }
        j = 0;
        mx_printchar('\n');
        if (i % count_per_column == 0)
            break;
    }
}

static int get_spaces(int max_len) {
    int spaces_count = 0;

    if (max_len % 8 == 0)
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8 != 0)
            spaces_count++;
    }
    return spaces_count;
}

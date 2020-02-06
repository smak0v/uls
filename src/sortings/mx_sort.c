#include "uls.h"

static void proccess_output(t_settings *settings, t_list **list,
                            bool many_lists, bool *is_first) {
    if (settings->is_atty || settings->has_output_format_flag) {
        if (settings->mode == columns) {
            if (settings->print_xcols)
                mx_print_x_columns(list, settings, many_lists, is_first);
            else
                mx_print_columns(list, settings, many_lists, is_first);
        }
        else if (settings->mode == table)
            mx_print_long(list, settings, many_lists, is_first);
        else if (settings->mode == commas)
            mx_print_stream(list, settings, many_lists, is_first);
        else
            mx_print_force(list, settings, many_lists, is_first);
    } else
        mx_print_force(list, settings, many_lists, is_first);
}

void mx_sort(t_list **list, bool (*cmp_1)(void *a, void *b),
             bool (*cmp_2)(void *a, void *b), t_settings *settings) {
    t_list *node = *list;
    t_list *inner = NULL;
    bool many_lists = node->next != NULL ? true : false;
    bool is_first = true;

    // if (cmp_1)
    //     mx_list_merge_sort(&node, cmp_1);
    // *list = node;
    // while (node) {
        inner = (t_list *)node->next;
        if (cmp_2)
            mx_list_merge_sort(&inner, cmp_2);
        node->next = inner;
        proccess_output(settings, &node, many_lists, &is_first);
        // node = node->next;
        // if (node)
        //     mx_printchar('\n');
    // }
    cmp_1 = NULL;
}

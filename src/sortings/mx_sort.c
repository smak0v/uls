#include "uls.h"

static void proccess_output(t_settings *settings, t_list **list) {
    if (settings->is_atty || settings->has_output_format_flag) {
        if (settings->mode == columns) {
            if (settings->print_xcols)
                mx_print_x_columns(list, settings);
            else
                mx_print_columns(list, settings);
        }
        else if (settings->mode == table)
            mx_print_long(list, settings);
        else if (settings->mode == commas)
            mx_print_stream(list, settings);
        else
            mx_print_force(list, settings);
    } else
        mx_print_force(list, settings);
}

void mx_sort(t_list **list, bool (*cmp)(void *a, void *b),
             t_settings *settings) {
    t_list *node = *list;
    t_list *inner = NULL;

    inner = (t_list *)node->next;
    if (cmp)
        mx_list_merge_sort(&inner, cmp);
    node->next = inner;
    proccess_output(settings, &node);
}

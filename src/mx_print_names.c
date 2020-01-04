#include "uls.h"

void mx_print_names(t_list **list, char *delim) {
    t_list *node = *list;

    while (node) {
        mx_printstr(((t_data *)node->data)->filename);
        if (node->next)
            mx_printstr(delim);
        else
            mx_printchar('\n');
        node = node->next;
    }
}

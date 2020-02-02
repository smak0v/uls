#include "uls.h"

void mx_sort(t_list *node, bool (*cmp_1)(void *a, void *b),
bool (*cmp_2)(void *a, void *b)) {
    t_list *inner = NULL;

    mx_list_quicksort(&node, cmp_1);
    while (node) {
        inner = ((t_list *)node->data)->next;
        mx_list_quicksort(&inner, cmp_2);
        node = node->next;
    }
}

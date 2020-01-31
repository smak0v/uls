#include "uls.h"

void mx_sort(t_list *node, bool (*cmp_1)(void *a, void *b),
bool (*cmp_2)(void *a, void *b)) {
    t_list *inner = NULL;

    mx_sort_list(node, cmp_1);
    while (node) {
        inner = ((t_list *)node->data)->next;
        mx_sort_list(inner, cmp_2);
        node = node->next;
    }
}

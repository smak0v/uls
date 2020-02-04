#include "uls.h"

void mx_sort(t_list **list, bool (*cmp_1)(void *a, void *b),
bool (*cmp_2)(void *a, void *b)) {
    t_list *node = *list;
    t_list *inner = NULL;

    mx_list_merge_sort(&node, cmp_1);
    while (node) {
        inner = ((t_list *)node->data)->next;
        mx_list_merge_sort(&inner, cmp_2);
        node = node->next;
    }
}

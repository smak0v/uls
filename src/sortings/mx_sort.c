#include "uls.h"

void mx_sort(t_list **list, bool (*cmp)(void *a, void *b)) {
    t_list *inner = (*list)->next;

    if (cmp)
        mx_list_merge_sort(&inner, cmp);
    (*list)->next = inner;
}

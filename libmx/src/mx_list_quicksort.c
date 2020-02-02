#include "libmx.h"

static t_list *get_last(t_list *head) {
    while (head && head->next)
        head = head->next;
    return head;
}

static t_list *partition(t_list *head, t_list *end, t_list **new_head,
    t_list **new_end, bool (*cmp)(void *a, void *b)) {
    t_list *pivot = end;
    t_list *prev = NULL;
    t_list *current = head;
    t_list *tail = pivot;
    t_list *tmp = NULL;

    while (current != pivot) {
        if (cmp(current, pivot)) {
            if (!(*new_head))
                *new_head = current;
            prev = current;
            current = current->next;
        }
        else {
            if (prev)
                prev->next = current->next;
            tmp = current->next;
            current->next = NULL;
            tail->next = current;
            tail = current;
            current = tmp;
        }
    }
    if (!(*new_head))
        *new_head = pivot;
    *new_end = tail;
    return pivot;
}

static t_list *quicksort(t_list *head, t_list *end,
bool (*cmp)(void *a, void *b)) {
    t_list *new_head = NULL;
    t_list *new_end = NULL;
    t_list *pivot = NULL;
    t_list *tmp = NULL;

    if (!head || head == end)
        return head;
    pivot = partition(head, end, &new_head, &new_end, cmp);
    if (new_head != pivot) {
        tmp = new_head;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        new_head = quicksort(new_head, tmp, cmp);
        tmp = get_last(new_head);
        tmp->next = pivot;
    }
    pivot->next = quicksort(pivot->next, new_end, cmp);
    return new_head;
}

void mx_list_quicksort(t_list **list, bool (*cmp)(void *a, void *b)) {
    *list = quicksort(*list, get_last(*list), cmp);
}

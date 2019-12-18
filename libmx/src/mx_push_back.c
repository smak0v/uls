#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *new = mx_create_node(data);
    t_list *last = NULL;

    if (!list || *list == NULL) {
        list = &new;
        return;
    }

    last = *list;

    while (last->next)
        last = last->next;
    last->next = new;
}

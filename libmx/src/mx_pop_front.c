#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *p = NULL;

    if (!head || !(*head)) 
        return ;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        p = (*head)->next;
        (*head)->data = NULL;
        free(*head); 
        *head = p;
    }
}

void mx_clear_list(t_list **list) {
    while (list && *list) {
        free((*list)->data);
        mx_pop_front(list);    
    }
}

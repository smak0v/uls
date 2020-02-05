#include "uls.h"

void mx_clear_errors_list(t_list **list) {
    while (list && *list) {
        free((*list)->data);
        mx_pop_front(list);    
    }
}

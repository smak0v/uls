#include "uls.h"

void mx_clear_list(t_list **list) {
    while (list && *list) {
        free((*list)->data);
        mx_pop_front(list);    
    }
}

static void free_t_data(t_data *tdata) {
    free(tdata->filename);
    free(tdata->full_filename);
    free(tdata->permissions);
    free(tdata->owner);
    free(tdata->group);
    free(tdata->symlink);
    if (tdata->major)
        free(tdata->major);
    if (tdata->minor)
        free(tdata->minor);
    free(tdata);
    tdata = NULL;
}

void mx_clear_tdata_list(t_list **list) {
    while (list && *list) {
        free_t_data((*list)->data);
        mx_pop_front(list);    
    }
}



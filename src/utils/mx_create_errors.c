#include "uls.h"

void mx_create_error(t_list **errlist, char *fname) {
    t_error *error = malloc(sizeof(t_error));

    error->filename = fname;
    error->error = errno;
    mx_push_front(errlist, error);
}

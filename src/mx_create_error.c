#include "uls.h"

t_error *mx_create_error(char *filename, char *error, int is_dir) {
    t_error *err = (t_error *)malloc(sizeof(t_error));

    err->filename = filename;
    err->error = error;
    err->is_dir = is_dir;
    return err;
}

#include "uls.h"

void mx_process_R(char **flags, t_list **list, char *path, char *filename) {
    char *tmp = mx_strjoin(path, "/");
    char *str = mx_strjoin(tmp, filename);

    mx_read_data(flags, (char **) mx_create_node(NULL), list, str);
    mx_strdel(&tmp);
}

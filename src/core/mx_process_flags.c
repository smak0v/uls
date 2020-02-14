#include "uls.h"

bool mx_check_flags(t_settings *s, t_dnt *dir) {
    if ((!mx_strcmp(dir->d_name, ".") || !mx_strcmp(dir->d_name, ".."))
        && !s->a)
        return true;
    else if (dir->d_name[0] == '.' && (!s->a && !s->A))
        return true;
    return false;
}

void mx_check_R(t_list *data, t_settings *s) {
    t_list *node = NULL;

    if (!data) {
        return;
    }
    node = data->next;

    if (s->R) {
        while (node) {
            t_data *info = node->data;

            if (info->is_dir && mx_strcmp(info->filename, ".")
                && mx_strcmp(info->filename, "..")) {
                    mx_printchar('\n');
                    mx_read_data(s, NULL, info->full_filename);
                }

            node = node->next;
        }
    }
}

#include "uls.h"

static void process_dirlist(t_list **dirlist, t_settings *s, int fls_bool) {
    t_list *node = (*dirlist)->next;
    int break_line = 0;

    node = (*dirlist)->next;
    mx_sort_data_list(dirlist, s);
    node = (*dirlist)->next;

    while (node) {
        if (break_line || fls_bool)
            mx_printchar('\n');
        else
            break_line = 1;
        mx_read_dir(s, ((t_data *)node->data)->filename);
        node = node->next;
    }
}

static void process_errors(t_list **errors) {
    mx_sort_errors(errors);
    mx_print_uls_error(*errors);
}

static bool save_file_or_error(t_settings *s, char *f, t_list **err) {
    if (errno != 20 || f[mx_strlen(f) - 1] == '/') {
        mx_create_error(err, f);
        s->not_found = 1;
        return false;
    }
    return true;
}

static t_list *dir_loop(t_settings *s, char **f, t_list **dls, t_list **fls) {
    t_list *errors = NULL;
    DIR *dir = NULL;
    t_st st;

    for (int i = 0; f && f[i]; ++i) {
        dir = opendir(f[i]);
        if ((!lstat(f[i], &st) && dir) || errno == 13) {
            if (errno == 13)
                s->not_found = 1;
            if (MX_IS_LNK(st.st_mode)
                && f[i][mx_strlen(f[i])] != '/' && s->mode == table)
                mx_push_back(fls, mx_write_data(s, st, f[i], f[i]));
            else
                mx_push_back(dls, mx_write_data(s, st, f[i], f[i]));
        }
        else if (save_file_or_error(s, f[i], &errors))
                mx_push_back(fls, mx_write_data(s, st, f[i], f[i]));
        dir ? closedir(dir) : 0;
    }
    return errors;
}

void mx_process_files(t_settings *setup, char **files) {
    t_list *errors = NULL;
    t_list *dirlist = mx_create_node(mx_memalloc(sizeof(t_data)));
    t_list *filelist = mx_create_node(mx_memalloc(sizeof(t_data)));
    int files_bool = 0;

    ((t_data *)dirlist->data)->filename = mx_strdup("DIRS");
    ((t_data *)filelist->data)->filename = mx_strdup(FILES);
    errors = dir_loop(setup, files, &dirlist, &filelist);
    process_errors(&errors);

    if (filelist->next) {
        mx_sort_data_list(&filelist, setup);
        mx_proccess_output(&filelist, setup);
        files_bool = 1;
    }
    mx_clear_tdata_list(&filelist);

    if (dirlist->next)
        process_dirlist(&dirlist, setup, files_bool);
    mx_clear_tdata_list(&dirlist);
}

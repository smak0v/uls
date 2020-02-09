#include "uls.h"

static void process_dirlist(t_list **dirlist, t_settings *s, int fls_bool) {
    t_list *node = (*dirlist)->next;
    int break_line = 0;

    mx_sort_data_list(dirlist, s);
    while (node) {
        if (break_line || fls_bool)
            mx_printchar('\n');
        else
            break_line = 1;   
        mx_read_dir(s, ((t_data *)node->data)->filename);
        node = node->next;
    }
    mx_clear_list(dirlist);
}

static void process_errors(t_list **errors) {
    mx_sort_errors(errors);
    mx_print_uls_error(*errors);
    mx_clear_list(errors);
}

static t_list *dir_loop(t_settings *s, char **f, t_list **dls, t_list **fls) {
    t_list *errors = NULL;
    DIR *dir;
    t_st st;

    for (int i = 0; f && f[i]; i++) {
        dir = opendir(f[i]);
        if (!lstat(f[i], &st) && dir)
            mx_push_back(dls, mx_write_data(s, st, f[i], f[i]));
        else {
            if (errno == 20) {
                mx_push_back(fls, mx_write_data(s, st, f[i], f[i]));
            }
            else if (errno == 2) {
                mx_create_error(&errors, f[i]);
                s->not_found = 1;
            }
            else
                mx_create_error(&errors, f[i]);
        }
    }
    return errors;
}

void mx_process_files(t_settings *setup, char **files) {
    t_list *errors = NULL;
    t_list *dirlist = mx_create_node(malloc(sizeof(t_data)));
    t_list *filelist = mx_create_node(malloc(sizeof(t_data)));
    int files_bool = 0;

    ((t_data *)dirlist->data)->filename = "DIRS";
    ((t_data *)filelist->data)->filename = FILES;

    errors = dir_loop(setup, files, &dirlist, &filelist);
    process_errors(&errors);

    if (filelist->next) {
        mx_sort_data_list(&filelist, setup);
        mx_proccess_output(&filelist, setup);
        // mx_clear_tdata_list(&filelist);
        files_bool = 1;
    }

    if (dirlist->next)
        process_dirlist(&dirlist, setup, files_bool);
}

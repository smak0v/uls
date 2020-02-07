#include "uls.h"
#include <stdio.h>

static t_data *write_data(t_settings *s, t_st st, char *full_fnm, char *fnm) {
    t_data *info = malloc(sizeof(t_data));

    info->filename = mx_strdup(fnm);
    info->full_filename = mx_strdup(full_fnm);
    info->is_dir = MX_IS_DIR(st.st_mode);
    mx_process_l(st, info, s);

    return info;
}

static bool check_flags(t_settings *s, t_dnt *dir) {
    if ((!mx_strcmp(dir->d_name, ".") || !mx_strcmp(dir->d_name, ".."))
        && !s->a)
        return true;
    else if (dir->d_name[0] == '.' && (!s->a && !s->A))
        return true;
    return false;
}

static void check_R(t_list *data, t_settings *s) {
    t_list *node = NULL;

    if (!data) {
        return ;
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

static int gather_data(t_list **data, t_dnt *dir, t_settings *s, char *dnm) {
    char *full_filename = mx_get_full_filename(dnm, dir->d_name);;
    t_data *info = NULL;
    t_st st;

    if ((!mx_strcmp(dnm, "/dev/fd") || !mx_strcmp(dnm, "/dev/fd/")) && !(*data)->data) {
        lstat("/dev/fd", &st);
        (*data)->data = write_data(s, st, mx_strdup(dnm), mx_strdup(dnm));
    }
    if (lstat(full_filename, &st) != 0) {
        mx_strdel(&full_filename);
        return -1;
    }
    if (!mx_strcmp(dir->d_name, ".") && !(*data)->data) {
        (*data)->data = write_data(s, st, mx_strdup(dnm), mx_strdup(dnm));
    }
    if (check_flags(s, dir)) {
        mx_strdel(&full_filename);
        return 0;
    }
    info = write_data(s, st, full_filename, dir->d_name);
    mx_push_back(data, (void *)info);

    return 0;
}

static void read_dir(t_settings *setup, char *dname) {
    struct dirent *dirnt = NULL;
    t_list *data = NULL;
    DIR *dir = opendir(dname);
    t_list *errors = NULL;
    int errnum = 0;

    if (!dir)
        mx_create_error(&errors, dname);
    else {
        mx_push_front(&data, NULL);

        while ((dirnt = readdir(dir)) != NULL) {
            errnum = gather_data(&data, dirnt, setup, dname);
            if (errnum)
                mx_create_error(&errors, dname);
        }

        closedir(dir);
        mx_sort_data_list(&data, setup);
        mx_proccess_output(&data, setup);
    }
    mx_print_uls_error(errors);
    check_R(data, setup);
}

static void process_files(t_settings *setup, char **files) {
    DIR *dir = NULL;
    t_list *errors = NULL;
    t_list *dirlist = mx_create_node(malloc(sizeof(t_data)));
    t_list *filelist = mx_create_node(malloc(sizeof(t_data)));
    t_list *node = NULL;
    int files_bool = 0;
    t_st st;

    ((t_data *)dirlist->data)->filename = "DIRS";
    ((t_data *)filelist->data)->filename = FILES;

    for (int i = 0; files && files[i]; i++) {
        dir = opendir(files[i]);
        if (dir) {
            if (lstat(files[i], &st) == 0) {
                mx_push_back(&dirlist, write_data(setup, st, files[i], files[i]));
            }
        }
        else {
            if (errno == 20) {
                if (lstat(files[i], &st) == 0) {
                    mx_push_back(&filelist, write_data(setup, st, files[i], files[i]));
                }
                else
                    mx_printstr_endl("\033[31mShit happens!\033[0m");
            }
            else if (errno == 2) {
                mx_create_error(&errors, files[i]);
                setup->not_found = 1;
            }
            else {
                mx_create_error(&errors, files[i]);
            }
        }
    }

    mx_sort_errors(&errors);
    mx_print_uls_error(errors);
    mx_clear_list(&errors);
    bool break_line = false;

    if (filelist->next) {
        mx_sort_data_list(&filelist, setup);
        mx_proccess_output(&filelist, setup);
        // mx_clear_tdata_list(&filelist);
        files_bool = 1;
    }

    mx_sort_data_list(&dirlist, setup);
    node = dirlist->next;

    while (node) {
        if (break_line == true || files_bool)
            mx_printchar('\n');
        else
            break_line = true;
        
        read_dir(setup, ((t_data *)node->data)->filename);
        node = node->next;
    }
    mx_clear_list(&dirlist);
}


void mx_read_data(t_settings *setup, char **files, char *f) {
    if (files && mx_get_arr_length(files) > 1)
        setup->has_many_file_arguments = true;
    if (!files || !(*files)) {
        read_dir(setup, f);
    }
    else {
        process_files(setup, files);
    }
}

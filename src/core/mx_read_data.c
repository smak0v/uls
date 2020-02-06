#include "uls.h"

static t_data *write_data(t_settings *s, t_dnt *dir, t_st st, char *full_fnm, char *fnm) {
    t_data *info = malloc(sizeof(t_data));

    info->filename = fnm ? fnm : mx_strdup(dir->d_name);
    info->full_filename = full_fnm;
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
    t_list *node = data->next;

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

static void gather_data(t_list *data, t_dnt *dir, t_settings *s, char *dnm) {
    char *full_filename = NULL;
    t_data *info = NULL;
    t_st st;

    full_filename = mx_get_full_filename(dnm, dir->d_name);
    lstat(full_filename, &st);
    if (!mx_strcmp(dir->d_name, ".") && !data->data) {
        data->data = write_data(s, dir, st, mx_strdup(dnm), mx_strdup(dnm));
    }
    if (check_flags(s, dir)) {
        mx_strdel(&full_filename);
        return ;
    }
    info = write_data(s, dir, st, full_filename, NULL);
    mx_push_back(&data, (void *)info);
}

static char **read_dir_files(t_settings *setup, t_list **list, char *dname,
                             char **files) {
    struct dirent *dirnt = NULL;
    t_st *st = malloc(sizeof(struct stat));
    char *full_filename = NULL;
    DIR *dir = opendir(dname);
    char *file_i = NULL;

    while ((dirnt = readdir(dir)) != NULL) {
        file_i = mx_check_match(files, dname, dirnt->d_name);
        if (file_i) {
            full_filename = mx_get_full_filename(dname, dirnt->d_name);
            lstat(full_filename, st);
            mx_push_second(list, (void *)write_data(setup, dirnt, *st,
                           full_filename, file_i));
            mx_strdel(&full_filename);
            files = mx_pop_string_array(files, file_i);
        }
    }
    closedir(dir);
    free(st);
    return files;
}

static void process_leftovers(t_settings *setup, char **files) {
    char *dirname = NULL;
    t_list *data = mx_create_node(malloc(sizeof(t_data)));

    ((t_data *)data->data)->filename = mx_strdup(FILES);

    for (int i = 0; files && files[i];) {
        dirname = mx_get_dirname(files[i]);
        files = read_dir_files(setup, &data, dirname, files);
        free(dirname);
    }

    mx_sort_data_list(&data, setup);
    mx_proccess_output(&data, setup);
}

static void read_dir(t_settings *setup, char *dname) {
    struct dirent *dirnt = NULL;
    t_list *data = NULL;
    DIR *dir = opendir(dname);

    if (!dir) {
        //mx_printstr_endl(strerror(errno));
        return ;
    }

    mx_push_front(&data, NULL);
    while ((dirnt = readdir(dir)) != NULL) {
        gather_data(data, dirnt, setup, dname);
    }

    closedir(dir);
    mx_sort_data_list(&data, setup);
    mx_proccess_output(&data, setup);
    check_R(data, setup);
    mx_clear_tdata_list(&data);
}


static void process_files(t_settings *setup, char **files) {
    DIR *dir = NULL;
    t_list *err_list = NULL;
    t_list *dirlist = NULL;
    t_list *node = NULL;
    int files_bool = 0;

    for (int i = 0; files && files[i]; i++) {
        dir = opendir(files[i]);
        if (dir) {
            mx_push_back(&dirlist, mx_strdup(files[i]));
            files = mx_pop_string_array(files, files[i--]);
            closedir(dir);
        }
        else {
            if (errno != 20) {
                if (!err_list)
                    err_list = mx_create_node(mx_strdup(files[i]));
                else
                    mx_push_front(&err_list, mx_strdup(files[i]));
                files = mx_pop_string_array(files, files[i--]);
                setup->not_found = 1;
            }
        }
    }
    mx_sort_errors(&err_list);
    mx_print_not_found(err_list);
    mx_clear_list(&err_list);
    if (files) {
        process_leftovers(setup, files);
        files_bool = 1;
    }

    bool break_line = false;
    // TODO create list and sort it
    node = dirlist;
    while (node) {
        if (break_line == true || files_bool)
            mx_printchar('\n');
        else
            break_line = true;
        read_dir(setup, node->data);
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

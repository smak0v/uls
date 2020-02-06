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

static void check_R(t_list **lst, t_settings *s, t_data *info, t_dnt *dir) {
    if (s->R && info->is_dir && mx_strcmp(dir->d_name, ".") 
        && mx_strcmp(dir->d_name, "..")) {
        mx_read_data(lst, s, NULL, info->full_filename);
    }
}

static void gather_data(t_lists lists, t_dnt *dir, t_settings *s, char *dnm) {
    char *full_filename = NULL;
    t_data *info = NULL;
    t_list **lst = lists.list;
    t_list *node = lists.node;
    t_st st;

    full_filename = mx_get_full_filename(dnm, dir->d_name);
    lstat(full_filename, &st);
    if (!mx_strcmp(dir->d_name, ".") && !node->data) {
        node->data = write_data(s, dir, st, dnm, mx_strdup(dnm));
    }
    if (check_flags(s, dir)) {
        mx_strdel(&full_filename);
        return ;
    }
    info = write_data(s, dir, st, full_filename, NULL);
    mx_push_second(&node, (void *)info);

    check_R(lst, s, info, dir);
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
            mx_push_second((t_list **)&((*list)->data),
                         (void *)write_data(setup, dirnt, *st, full_filename, file_i));
            mx_strdel(&full_filename);
            files = mx_pop_string_array(files, file_i);
        }
    }
    closedir(dir);
    free(st);
    return files;
}

static void process_leftovers(t_settings *setup, char **files, t_list **data) {
    char *dirname = NULL;
    t_list *inner_node = NULL;

    mx_push_front(data, mx_create_node(malloc(sizeof(t_data))));
    inner_node = (*data)->data;
    ((t_data *)inner_node->data)->filename = mx_strdup(FILES);

    for (int i = 0; files && files[i];) {
        dirname = mx_get_dirname(files[i]);
        files = read_dir_files(setup, data, dirname, files);
        free(dirname);
    }
}

static void read_dir(t_settings *setup, t_list **list, char *dname, DIR *dir) {
    struct dirent *dirnt = NULL;
    t_list *node = NULL;
    t_lists lists;

    mx_push_front(list, mx_create_node(NULL)); // mx_create_node(mx_getdirinfo)
    node = (t_list *)(*list)->data;
    lists.list = list;
    lists.node = node;

    while ((dirnt = readdir(dir)) != NULL) {
        gather_data(lists, dirnt, setup, dname);
    }

    // mx_printstr_endl(((t_data *)node->data)->filename);
    mx_sort_and_output(&node, setup);
}



static void process_files(t_settings *setup, char **files, t_list **data) {
    DIR *dir = NULL;
    t_list *err_list = NULL;

    for (int i = 0; files && files[i]; i++) {
        dir = opendir(files[i]);
        if (dir) {
            read_dir(setup, data, files[i], dir);
            files = mx_pop_string_array(files, files[i--]);
            closedir(dir);
        }
        else {
            if (errno != 20) { // 20 == Not a directory error
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
    mx_clear_errors_list(&err_list);
    if (files) {
        process_leftovers(setup, files, data);
    }
}


void mx_read_data(t_list **data, t_settings *setup, char **files, char *f) {
    DIR *directory = NULL;

    if (files && mx_get_arr_length(files) > 1)
        setup->has_many_file_arguments = true;
    if (!files || !(*files)) {
        directory = opendir(f);
        if (!directory) {
            // mx_printstr_endl(strerror(errno));
            return;
        }
        read_dir(setup, data, f, directory);
        closedir(directory);
    }
    else {
        process_files(setup, files, data);
    }
}

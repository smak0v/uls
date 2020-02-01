#include "uls.h"

static t_data *write_data(t_settings *s, t_dnt *dir, t_st st, char *dname) {
    t_data *info = malloc(sizeof(t_data));

    info->filename = mx_strdup(dir->d_name);
    info->full_filename = mx_get_full_filename(dname, info->filename);
    info->is_dir = MX_IS_DIR(st.st_mode);
    mx_process_l(st, info, s);
    if (s->append_slash)
        mx_append_slash(&info, s);
    else if (s->append_type_sign)
        mx_append_type_sign(st, &info, s);

    return info;
}


static void gather_data(t_lists lists, t_dnt *dir, t_st st, t_settings *s,
                        char *dnm) {
    t_data *info = NULL;
    t_list **lst = lists.list;
    t_list *node = lists.node;

    if (!mx_strcmp(dir->d_name, ".") && !node->data) {
        node->data = write_data(s, dir, st, dnm);
        free(((t_data *)node->data)->filename);
        ((t_data *)node->data)->filename = mx_strdup(dnm);
    }
    if ((!mx_strcmp(dir->d_name, ".") || !mx_strcmp(dir->d_name, "..")) 
        && !s->a)
        return;
    else if (dir->d_name[0] == '.' && (!s->a && !s->A))
        return;
    info = write_data(s, dir, st, dnm);
    if (s->R && info->is_dir && mx_strcmp(dir->d_name, ".") 
        && mx_strcmp(dir->d_name, ".."))
        mx_read_data(lst, s, NULL, info->full_filename);
    mx_push_back(&node, (void *)info);
}


static char **read_dir_files(t_settings *setup, t_list **list, char *dname, 
                           char **files) {
    struct dirent *dirnt = NULL;
    struct stat *st = malloc(sizeof(struct stat));
    char *full_filename = NULL;
    DIR *dir = opendir(dname);
    char *file_i = NULL;
    t_lists lists;

    while ((dirnt = readdir(dir)) != NULL) {
        file_i = mx_check_match(files, dname, dirnt->d_name);
        if (file_i) {
            full_filename = mx_get_full_filename(dname, dirnt->d_name);
            lstat(full_filename, st);
            lists.list = list;
            lists.node = (*list)->data;
            gather_data(lists, dirnt, *st, setup, dname);
            mx_strdel(&full_filename);
            files = mx_pop_string_array(files, file_i);
        }
    }
    free(st);
    st = NULL;
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
    struct stat *st = malloc(sizeof(struct stat));
    char *full_filename = NULL;
    t_list *node = NULL;
    t_lists lists;

    mx_push_front(list, mx_create_node(NULL)); // mx_create_node(mx_getdirinfo)
    node = (*list)->data;
    lists.list = list;
    lists.node = node;

    while ((dirnt = readdir(dir)) != NULL) {
        full_filename = mx_get_full_filename(dname, dirnt->d_name);
        lstat(full_filename, st);
        gather_data(lists, dirnt, *st, setup, dname);
        mx_strdel(&full_filename);
    }
    free(st);
    st = NULL;
}


static void process_files(t_settings *setup, char **files, t_list **data) {
    DIR *dir = NULL;

    for (int i = 0; files && files[i]; i++) {
        dir = opendir(files[i]);
        if (dir) {
            read_dir(setup, data, files[i], dir);
            files = mx_pop_string_array(files, files[i--]);
            closedir(dir);
        }
        else {
            if (errno != 20) { // 20 == Not a directory error
                // mx_print_no_such_error(files[i]);
                files = mx_pop_string_array(files, files[i--]);
                setup->not_found = 1;
            }
        }
    }
    if (files) {
        process_leftovers(setup, files, data);
    }
}


void mx_read_data(t_list **data, t_settings *setup, char **files, char *f) {
    DIR *directory = NULL;

    if (!files || !(*files)) {
        directory = opendir(f);
        if (!directory) {
            mx_printstr_endl(strerror(errno));
            return;
        }
        read_dir(setup, data, f, directory);
        closedir(directory);
    }
    else {
        process_files(setup, files, data);
    }

    //free(f);
}

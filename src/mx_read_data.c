#include "uls.h"

static void write_data(t_data **info_ptr, t_dnt *dir, t_st st, char *dname) {
    t_data *info = *info_ptr;

    info->filename = mx_strdup(dir->d_name);
    info->full_filename = mx_get_full_filename(dname, info->filename);
    info->is_dir = MX_IS_DIR(st.st_mode);
    mx_process_l(st, info);
}


static void gather_data(t_list **lst, t_dnt *dir, t_st st, char *dnm,
                        t_settings *s) {
    t_list *inner_data = (*lst)->data;
    t_data *info = NULL;

    if ((!mx_strcmp(dir->d_name, ".") || !mx_strcmp(dir->d_name, "..")) 
        && mx_search_arr(s, a))
        return;
    else if (dir->d_name[0] == '.' && !mx_search_arr(s, A))
        return;

    info = malloc(sizeof(t_data));
    write_data(&info, dir, st, dnm);

    if (mx_search_arr(s, R) && info->is_dir)
        mx_read_data(lst, s, NULL, info->full_filename);
    
    mx_push_back(&inner_data, (void *)info);
}


static char **read_dir_files(t_settings *setup, t_list **list, char *dname, 
                           char **files) {
    struct dirent *dirnt = NULL;
    struct stat *st = malloc(sizeof(struct stat));
    char *full_filename = NULL;
    DIR *dir = opendir(dname);
    char *file_i = NULL;

    while ((dirnt = readdir(dir)) != NULL) {
        file_i = mx_check_match(files, dname, dirnt->d_name);
        if (file_i) {
            full_filename = mx_get_full_filename(dname, dirnt->d_name);
            lstat(full_filename, st);
            gather_data(list, dirnt, *st, dname, setup);
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

    mx_push_front(data, mx_create_node(mx_strdup("files")));

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

    mx_push_front(list, mx_create_node(mx_strdup(dname))); // mx_create_node(mx_getdirinfo)

    while ((dirnt = readdir(dir)) != NULL) {
        full_filename = mx_get_full_filename(dname, dirnt->d_name);
        lstat(full_filename, st);
        gather_data(list, dirnt, *st, dname, setup);
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
    if (files)
        process_leftovers(setup, files, data);
}


void mx_read_data(t_list **data, t_settings *setup, char **files, char *f) {
    DIR *directory = NULL;

    if (!files || !(*files)) {
        directory = opendir(f);
        read_dir(setup, data, f, directory);
    }
    else {
        process_files(setup, files, data);
    }
}

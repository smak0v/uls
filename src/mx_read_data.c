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
    t_list *node = data;

    if (s->R) {
        while (node) {
            t_data *info = node->data;
        
            if (info->is_dir && mx_strcmp(info->filename, ".") 
                && mx_strcmp(info->filename, ".."))
                mx_read_data(s, NULL, info->full_filename);
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
        data->data = write_data(s, dir, st, dnm, mx_strdup(dnm));
    }
    if (check_flags(s, dir)) {
        mx_strdel(&full_filename);
        return ;
    }
    info = write_data(s, dir, st, full_filename, NULL);
    mx_push_back(&data, (void *)info);
}

// static char **read_dir_files(t_settings *setup, t_list **list, char *dname,
//                              char **files) {
//     struct dirent *dirnt = NULL;
//     t_st *st = malloc(sizeof(struct stat));
//     char *full_filename = NULL;
//     DIR *dir = opendir(dname);
//     char *file_i = NULL;

//     while ((dirnt = readdir(dir)) != NULL) {
//         file_i = mx_check_match(files, dname, dirnt->d_name);
//         if (file_i) {
//             full_filename = mx_get_full_filename(dname, dirnt->d_name);
//             lstat(full_filename, st);
//             mx_push_second((t_list **)&((*list)->data),
//                          (void *)write_data(setup, dirnt, *st, full_filename, file_i));
//             mx_strdel(&full_filename);
//             files = mx_pop_string_array(files, file_i);
//         }
//     }
//     closedir(dir);
//     free(st);
//     return files;
// }

// static void process_leftovers(t_settings *setup, char **files, t_list **data) {
//     char *dirname = NULL;

//     mx_push_front(data, malloc(sizeof(t_data)));
//     ((t_data *)(*data)->data)->filename = mx_strdup(FILES);

//     for (int i = 0; files && files[i];) {
//         dirname = mx_get_dirname(files[i]);
//         files = read_dir_files(setup, data, dirname, files);
//         free(dirname);
//     }
// }

static void read_dir(t_settings *setup, char *dname, DIR *dir) {
    struct dirent *dirnt = NULL;
    t_list *data = NULL;

    mx_push_front(&data, NULL); // mx_create_node(mx_getdirinfo)

    while ((dirnt = readdir(dir)) != NULL) {
        gather_data(data, dirnt, setup, dname);
    }

    mx_sort_and_output(&data, setup);
    check_R(data, setup);
}



// static void process_files(t_settings *setup, char **files) {
//     DIR *dir = NULL;
//     t_list *err_list = NULL;

//     for (int i = 0; files && files[i]; i++) {
//         dir = opendir(files[i]);
//         if (dir) {
//             read_dir(setup, files[i], dir);
//             files = mx_pop_string_array(files, files[i--]);
//             closedir(dir);
//         }
//         else {
//             if (errno != 20) { // 20 == Not a directory error
//                 if (!err_list)
//                     err_list = mx_create_node(mx_strdup(files[i]));
//                 else
//                     mx_push_front(&err_list, mx_strdup(files[i]));
//                 files = mx_pop_string_array(files, files[i--]);
//                 setup->not_found = 1;
//             }
//         }
//     }
//     mx_sort_errors(&err_list);
//     mx_print_not_found(err_list);
//     mx_clear_errors_list(&err_list);
//     if (files) {
//         process_leftovers(setup, files);
//     }
// }


void mx_read_data(t_settings *setup, char **files, char *f) {
    DIR *directory = NULL;

    // if (files && mx_get_arr_length(files) > 1)
    //     setup->has_many_file_arguments = true;
    if (!files || !(*files)) {
        directory = opendir(f);
        if (!directory) {
            // mx_printstr_endl(strerror(errno));
            return;
        }
        read_dir(setup, f, directory);
        closedir(directory);
    }
    // else {
    //     process_files(setup, files);
    // }
}

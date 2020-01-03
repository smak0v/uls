#include "uls.h"

static void read_data(t_list **list, char *file, DIR *direct, char **flags);
static void gather_data(t_list **list, t_list *data, t_dnt *dir, char **flag, t_st st, char *full_filename);

void mx_read_data(char **flags, char **files, t_list **list, char *filename) {
    DIR *directory = NULL;

    if (!files || !(*files)) {
        directory = opendir(filename);
        read_data(list, filename, directory, flags);
        closedir(directory);
    }
    else
        for (int i = 0; i < mx_get_arr_length(files); i++){
            directory = opendir(files[i]);
            if (directory) {
                read_data(list, files[i], directory, flags);
                closedir(directory);
            }
            else {
                // TODO gather file data
            }
        }
}

static void read_data(t_list **list, char *file, DIR *direct, char **flags) {
    t_list *data = NULL;
    t_list *inner_data = NULL;
    struct dirent *dir = NULL;
    struct stat *st = malloc(sizeof(struct stat));
    char *full_filename = NULL;
    char *tmp = NULL;

    mx_push_back(list, mx_create_node(file));
    data = *list;
    while (data->next)
        data = data->next;
    inner_data = (t_list *)data->data;
    while ((dir = readdir(direct)) != NULL) {
        mx_printstr_endl(dir->d_name);
        tmp = mx_strjoin(file, "/");
        full_filename = mx_strjoin(tmp, dir->d_name);
        mx_strdel(&tmp);
        lstat(full_filename, st);
        gather_data(&data, inner_data, dir, flags, *st, full_filename);
        mx_strdel(&full_filename);
    }
    free(st);
    st = NULL;
}

static void gather_data(t_list **list, t_list *data, t_dnt *dir, char **flag, t_st st, char *full_filename) {
    t_data *info = NULL;

    if (!mx_search_strarr(flag, "a") && dir->d_name[0] == '.')
        return;
    info = malloc(sizeof(t_data));
    info->filename = mx_strdup(dir->d_name);
    info->full_filename = mx_strdup(full_filename);
    info->is_dir = IS_DIR(st.st_mode);
    if (mx_search_strarr(flag, "l"))
        mx_process_l(dir, st, info);
    else if (mx_search_strarr(flag, "R") && info->is_dir)
        mx_process_R(flag, list, (char *)data->data, info->filename);
    mx_push_back(&data, (void *)info);
}

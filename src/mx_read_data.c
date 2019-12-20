#include "uls.h"
#include <stdio.h>

// static void process_R(char **flags, t_list **list, char *path, char *filename) {
//     // I'm rewriting it
// }


static void process_l(t_dnt *dir, t_st st, t_data *data) {
    struct passwd *passwd_ptr = getpwuid(st.st_uid);

    data->blocks_count = st.st_blocks;
    data->permissions = mx_get_permissions(st.st_mode);
    data->acl_text = mx_get_acl(dir->d_name);
    data->xattr_text = mx_get_xattr(dir->d_name);
    data->links_count = mx_itoa(st.st_nlink);
    data->owner = mx_strdup(passwd_ptr->pw_name);
    data->group = mx_get_group(st.st_gid);
    data->file_size = mx_itoa(st.st_size);
    data->last_modified = mx_format_time(ctime(&st.st_mtimespec.tv_sec));
    data->symlink = mx_get_symlink(dir->d_name, st.st_size);
}


static void gather_data(t_list **list, t_list *data, t_dnt *dir, char **flag, t_st st) {
    t_data *info = NULL;
    
    if (!mx_search_strarr(flag, "a") && dir->d_name[0] == '.') {
        return;
    }

    info = malloc(sizeof(t_data));
    info->filename = dir->d_name;
    info->is_dir = S_ISDIR(st.st_mode);

    if (mx_search_strarr(flag, "l")) {
        process_l(dir, st, info);
    }
    // else if (mx_search_strarr(flag, "R") && info->is_dir) {
    //     process_R(flag, list, (char *) data->data, info->filename);
    // }

    // Temporary code to avoid unused variable warning
    t_list *node = *list;
    node = NULL;

    mx_push_back(&data, (void *) info);
}

// WILL REFACTOR THIS
t_list *mx_read_data(char **flags, char **files, t_list **list, char *dirname) {
    t_list *data = NULL;
    t_list *inner_data = NULL;
    DIR *directory = opendir(dirname);
    struct dirent *dir = NULL;
    struct stat *st = malloc(sizeof(struct stat));

    mx_push_back(list, mx_create_node(dirname));
    data = *list;
    while (data->next) {
        data = data->next;
    }
    inner_data = (t_list *) data->data;
    while ((dir = readdir(directory)) != NULL) {
        char *tmp = mx_strjoin(dirname, "/");
        char *path = mx_strjoin(tmp, dir->d_name);
        if (lstat(path, st) != 0) {
            // SOME ERROR HANDLING HERE?
            mx_printstr("error in gather data: stat() != 0\n");
            exit(-1);
        }
        if (!files || *files == NULL) {
            gather_data(&data, inner_data, dir, flags, *st);
        }
        else if (mx_search_strarr(files, dir->d_name)) {
            if (S_ISDIR(st->st_mode)) {
                mx_read_data(flags, NULL, list, dir->d_name);
            }
            else {
                gather_data(&data, inner_data, dir, flags, *st);
            }
        }
    }
    free(st);
    return data;
}

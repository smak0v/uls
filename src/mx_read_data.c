#include "uls.h"

static void process_R(char **flags, t_list **list, t_list *data, char *path) {
    t_data *info = (t_data *) data->data;
    char *tmp = mx_strjoin(path, "/");
    char *str = mx_strjoin(tmp, info->filename);

    mx_read_data(flags, NULL, list, str);
    mx_strdel(&tmp);
    mx_strdel(&str);
}


static void process_l(t_dnt *dir, t_st st, t_data *data) {
    struct passwd *passwd_ptr = getpwuid(st.st_uid);

    data->permissions = mx_get_permissions(st.st_mode);
    data->acl = acl_get_file(dir->d_name, ACL_TYPE_EXTENDED);
    data->xattr = listxattr(dir->d_name, NULL, 0, XATTR_NOFOLLOW);
    data->links_count = st.st_nlink;
    data->owner = passwd_ptr->pw_name;
    data->group = "GROUP"; // How to get string from st.st_gid?
    data->file_size = st.st_size;
    data->last_modified = mx_format_time(ctime(&st.st_mtimespec.tv_sec));
}


static void gather_data(t_list **list, t_list *data, t_dnt *dir, char **flag, t_st st) {
    t_data *info = malloc(sizeof(t_data));
    info->filename = dir->d_name;
    info->is_dir = S_ISDIR(st.st_mode);

    if (mx_search_strarr(flag, "l")) {
        process_l(dir, st, info);
    }
    else if (mx_search_strarr(flag, "R") && info->is_dir) {
        process_R(flag, list, data, info->filename);
    }

    mx_push_back(&data, (void *) data);
}


t_list *mx_read_data(char **flags, char **files, t_list **list, char *dirname) {
    mx_printstr("hi1\n");
    t_list *data = mx_create_node((void *) dirname);
    DIR *directory = opendir(dirname);
    struct dirent *dir = NULL;
    struct stat *st = malloc(sizeof(struct stat));

    mx_printstr("hi2\n");
    mx_push_back(list, (void *) data);
    mx_printstr("hi3\n");
    while ((dir = readdir(directory)) != NULL) {
        //printf("ghee\n");
        if (stat(dir->d_name, st) != 0) {
            // SOME ERROR HANDLING HERE?
            mx_printstr("error in gather data: stat() != 0\n");
            exit(-1);
        }
        if (*files == NULL) {
            mx_printstr("hello\n");
            gather_data(list, data, dir, flags, *st);
            mx_printstr("yo\n");
        }
        else if (mx_search_strarr(files, dir->d_name)) {
            mx_printstr("shit\n");
            if (S_ISDIR(st->st_mode)) {
                mx_printstr("nigga\n");
                mx_read_data(flags, NULL, list, dir->d_name);
                mx_printstr("mofo\n");
            }
            else {
                mx_printstr("hi\n"); 
                gather_data(list, data, dir, flags, *st);
            }
        }
    }
    mx_printstr("wtf?\n");
    free(st);
    return data;
}

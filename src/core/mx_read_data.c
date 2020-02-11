#include "uls.h"

t_data *mx_write_data(t_settings *s, t_st st, char *full_fnm, char *fnm) {
    t_data *info = mx_memalloc(sizeof(t_data));

    info->filename = mx_strdup(fnm);
    info->full_filename = mx_strdup(full_fnm);
    info->is_dir = MX_IS_DIR(st.st_mode);
    mx_process_info(st, info, s);
    return info;
}

static void kostyl(t_list **data, char *dnm, t_settings *s) {
    t_st st;

    if ((!mx_strcmp(dnm, "/dev/fd")
        || !mx_strcmp(dnm, "/dev/fd/"))
        && !(*data)->data) {
        lstat(dnm, &st);
        (*data)->data = mx_write_data(s, st, dnm, dnm);
    }
}

static int gather_data(t_list **data, t_dnt *dir, t_settings *s, char *dnm) {
    char *full_filename = mx_get_full_filename(dnm, dir->d_name);;
    t_data *info = NULL;
    t_st st;

    kostyl(data, dnm, s);
    if (lstat(full_filename, &st) != 0) {
        mx_strdel(&full_filename);
        return -1;
    }
    if (!mx_strcmp(dir->d_name, ".") && !(*data)->data) {
        (*data)->data = mx_write_data(s, st, dnm, dnm);
    }
    if (mx_check_flags(s, dir)) {
        mx_strdel(&full_filename);
        return 0;
    }
    info = mx_write_data(s, st, full_filename, dir->d_name);
    mx_push_back(data, (void *)info);
    mx_strdel(&full_filename);
    return 0;
}

void mx_read_dir(t_settings *setup, char *dname) {
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
        }
        closedir(dir);
        mx_sort_data_list(&data, setup);
        mx_proccess_output(&data, setup);
    }
    mx_print_uls_error(errors);
    mx_check_R(data, setup);
    mx_clear_tdata_list(&data);
}

void mx_read_data(t_settings *setup, char **files, char *f) {
    if (files && mx_get_arr_length(files) > 1)
        setup->has_many_file_arguments = true;
    if (!files || !(*files)) {
        mx_read_dir(setup, f);
    }
    else {
        mx_process_files(setup, files);
    }
}

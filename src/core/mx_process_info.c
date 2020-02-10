#include "uls.h"

static void proccess_time(t_settings *settings, t_st st, t_data *data) {
    if (settings->sorting == mod_time || settings->time == mod) {
        data->last_modified = st.st_mtimespec.tv_sec;
        data->last_modified_nsec = st.st_mtimespec.tv_nsec;
    }
    else if (settings->sorting == crt_time || settings->time == crt) {
        data->creation_time = st.st_birthtimespec.tv_sec;
        data->creation_time_nsec = st.st_birthtimespec.tv_nsec;
    }
    else if (settings->sorting == acc_time || settings->time == acc) {
        data->last_access = st.st_atimespec.tv_sec;
        data->last_access_nsec = st.st_atimespec.tv_nsec;
    }
    else if (settings->sorting == chg_time || settings->time == chg) {
        data->last_changed = st.st_ctimespec.tv_sec;
        data->last_changed_nsec = st.st_ctimespec.tv_nsec;
    }
}

static void process_major_minor(t_data *data) {
    if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode)) {
        data->major = mx_get_major(data->st_rdev);
        data->minor = mx_get_minor(data->st_rdev);
    }
    else {
        data->major = NULL;
        data->minor = NULL;
    }
}

static void proccess_extras(t_settings *settings, t_st st, t_data *data) {
    char *full_name = data->full_filename;

    if (settings->sorting == size || settings->mode == table)
        data->file_size = st.st_size;
    if (settings->mode == table) {
        data->xattr_value_length = -1;
        data->blocks_count = st.st_blocks;
        data->has_acl = mx_has_acl(full_name);
        data->xattr_text = mx_get_xattr(full_name, &data->xattr_value_length);
        data->links_count = st.st_nlink;
        data->owner = mx_get_owner(st.st_uid, settings);
        data->group = mx_get_group(st.st_gid, settings);
        data->symlink = mx_get_symlink(data);
        data->st_rdev = st.st_rdev;
        process_major_minor(data);
    }
    proccess_time(settings, st, data);
}

void mx_process_info(t_st st, t_data *data, t_settings *settings) {
    if (settings->append_slash
        || settings->append_type_sign
        || settings->mode == table
        || settings->colored)
        data->mode = st.st_mode;
    if (settings->mode == table || settings->colored)
        data->permissions = mx_get_permissions(st.st_mode);
    if (settings->print_inode)
        data->inode = st.st_ino;
    proccess_extras(settings, st, data);
}

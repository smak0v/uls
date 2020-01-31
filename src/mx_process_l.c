#include "uls.h"

static void proccess_time(t_st st, t_data *data);
static void check_major_minor(t_data *data);

void mx_process_l(t_st st, t_data *data) {
    char *full_name = data->full_filename;

    data->xattr_value_length = -1;
    data->blocks_count = st.st_blocks;
    data->permissions = mx_get_permissions(st.st_mode);
    data->acl_text = mx_get_acl(full_name);
    data->xattr_text = mx_get_xattr(full_name, &data->xattr_value_length);
    data->links_count = mx_itoa(st.st_nlink);
    data->owner = mx_get_owner(st.st_uid);
    data->group = mx_get_group(st.st_gid);
    data->file_size = st.st_size;
    proccess_time(st, data);
    data->symlink = mx_get_symlink(full_name, st.st_size);
    data->mode = st.st_mode;
    data->st_rdev = st.st_rdev;
    data->inode = st.st_ino;
    check_major_minor(data);
}

static void proccess_time(t_st st, t_data *data) {
    data->last_modified = st.st_mtimespec.tv_sec;
    data->last_modified_nsec = st.st_mtimespec.tv_nsec;
    data->creation_time = st.st_birthtimespec.tv_sec;
    data->creation_time_nsec = st.st_birthtimespec.tv_nsec;
    data->last_access = st.st_atimespec.tv_sec;
    data->last_access_nsec = st.st_atimespec.tv_nsec;
    data->last_changed = st.st_ctimespec.tv_sec;
    data->last_changed_nsec = st.st_ctimespec.tv_nsec;
}

static void check_major_minor(t_data *data) {
    if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode)) {
        data->major = mx_get_major(data->st_rdev);
        data->minor = mx_get_minor(data->st_rdev);
    }
}

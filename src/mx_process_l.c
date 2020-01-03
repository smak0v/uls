#include "uls.h"

void mx_process_l(t_dnt *dir, t_st st, t_data *data) {
    data->xattr_value_length = -1;
    data->blocks_count = st.st_blocks;
    data->permissions = mx_get_permissions(st.st_mode);
    data->acl_text = mx_get_acl(dir->d_name);
    data->xattr_text = mx_get_xattr(dir->d_name, &data->xattr_value_length);
    data->links_count = mx_itoa(st.st_nlink);
    data->owner = mx_get_owner(st.st_uid);
    data->group = mx_get_group(st.st_gid);
    data->file_size = mx_itoa(st.st_size);
    data->last_modified = st.st_mtimespec.tv_sec;
    data->symlink = mx_get_symlink(data->full_filename, st.st_size);
    data->mode = st.st_mode;
    data->st_rdev = st.st_rdev;
}

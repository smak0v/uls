#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>

#include <uuid/uuid.h>

// Constants
#define ALLOWED_FLAGS "Ral"
// #define ALLOWED_FLAGS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"


// Structures
typedef struct dirent t_dnt;
typedef struct stat t_st;

typedef struct s_uls {
    char *permissions;
    bool acl;
    char *attrs_text;
    bool attrs;
    char *acl_text;
    nlink_t hard_links_count;
    uid_t owner_id;
    char *owner_name;
    gid_t group_id;
    char *group_name;
    off_t size_in_bytes;
    struct timespec access_time;
    struct timespec modification_time;
    struct timespec status_change_time;
    char *filename;
    char *symlink;
    ino_t serial_number;
    char *file_flags;
} t_uls;

typedef struct s_data {
    char *filename;
    bool is_dir;

    // -l
    blkcnt_t blocks_count;
    char *permissions;
    char *acl_text;
    char *xattr_text;
    char *links_count;
    char *owner;
    char *group;
    char *file_size;
    long last_modified;
    char *symlink;

    // -@
    ssize_t xattr_value_length;
} t_data;

// Functions
t_list *mx_read_data(char **flags, char **files, t_list **list, char *dirname);

char **mx_store_flags(int argc, char **argv);
char **mx_store_files(int argc, char **argv);
void mx_errors_handler(char **flags, char **files);
char *mx_check_flags(char **flags);
char *mx_format_time(char *lm_time);
void mx_print_spaces(int count);
char mx_get_file_type(mode_t mode);
bool mx_search_strarr(char **strarr, char *str);

char *mx_r_align(char *str, int spaces_count);
char *mx_l_align(char *str, int spaces_count);
void mx_right_align_links(t_list **list);
void mx_right_align_size(t_list **list);
void mx_left_align_owner(t_list **list);
void mx_left_align_group(t_list **list);

int mx_get_total(t_list **list);
char *mx_get_permissions(mode_t mode);
char *mx_get_acl(char *dirname);
char *mx_get_xattr(char *dirname, ssize_t *length);
char *mx_get_group(gid_t st_gid);
char *mx_get_symlink(char *dirname, off_t st_size);

void mx_sort_by_name(t_list **list);

void mx_print_total(t_list **list);
void mx_print_acl_xattr_or_nothing(t_data *data);
void mx_print_date(time_t date);

void mx_print_l(t_list **list);

#endif

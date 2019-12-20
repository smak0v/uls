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
    git_t group_id;
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
    char *permissions;
    bool acl;
    bool xattr;
    unsigned short links_count;
    char *owner;
    char *group;
    long long file_size;
    char *last_modified;
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
char *mx_get_permissions(mode_t mode);
void mx_print_permissions(mode_t mode);

#endif

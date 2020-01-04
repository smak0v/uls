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
#define ALLOWED_FLAGS "ACRalmx1"
#define MODE_FLAGS "Clmx1"
#define SORTING_FLAGS "Cx"
#define DATA_FLAGS "ARal"

// Macroses
#define MX_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define MX_IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)

// Structures
typedef struct dirent t_dnt;

typedef struct stat t_st;

typedef enum e_modes {
    columns,
    table,
    commas,
    line_break
} t_mode_enum;

typedef enum e_sorting {
    standard,
} t_sorting_enum;

typedef enum e_data {
    names,
    l,
    a,
    A,
    R
} t_data_enum;

typedef struct s_data {
    char *filename;
    char *full_filename;
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
    mode_t mode;
    int st_rdev;
    char *major;
    char *minor;

    // -@
    ssize_t xattr_value_length;
} t_data;

typedef struct s_settings {
    int mode;
    int sorting;
    int data;
} t_settings;

typedef struct s_max_len {
    int links_max_len;
    int owners_max_len;
    int groups_max_len;
    int sizes_max_len;
} t_max_len;

// Functions
t_settings *mx_setup(char **flags);
void mx_read_data(char **flags, char **files, t_list **list, char *dirname);
void mx_process_output(t_list **data, t_settings *settings);

void mx_process_l(t_dnt *dir, t_st st, t_data *data);
void mx_process_R(char **flags, t_list **list, char *path, char *filename);

char **mx_store_flags(int argc, char **argv);
char **mx_store_files(int argc, char **argv);
void mx_errors_handler(char **flags, char **files);
char *mx_check_flags(char **flags);
void mx_print_spaces(int count);
char mx_get_file_type(mode_t mode);
bool mx_search_strarr(char **strarr, char *str);
bool mx_check_chr_or_blk_device(t_list **list);

t_max_len *mx_get_max_len_struct(t_list *list);
int mx_get_total(t_list *list);
char *mx_get_permissions(mode_t mode);
char *mx_get_acl(char *dirname);
char *mx_get_xattr(char *dirname, ssize_t *length);
char *mx_get_group(gid_t st_gid);
char *mx_get_owner(uid_t st_uid);
char *mx_get_symlink(char *dirname, off_t st_size);
char *mx_get_major(int st_rdev);
char *mx_get_minor(int st_rdev);

void mx_sort_by_name(t_list **list);

void mx_print_total(t_list *list);
void mx_print_filename_and_total(t_list *node, t_list *inner_node);
void mx_print_acl_xattr_or_nothing(t_data *data);
void mx_print_date(time_t date);

void mx_print_l(t_list **list);

#endif

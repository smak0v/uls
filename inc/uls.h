#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>

#include <uuid/uuid.h>

// Constants
#define ALLOWED_FLAGS "ACFGRSTU@acfghilmnoprtux1"
#define MODE_FLAGS "Clgonmx1"
#define SORTING_FLAGS "Stlf"
#define FILES "f_I_l_E_s"

// Macroses
#define MX_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define MX_IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define MX_IS_EXEC(mode) ((mode) & S_IXUSR)
#define MX_MAX(x, y) (((x) > (y)) ? (x) : (y))

// Structures
typedef struct dirent t_dnt;

typedef struct stat t_st;

typedef struct s_lists {
    t_list **list;
    t_list *node;
} t_lists;

typedef enum e_modes {
    columns,
    table,
    commas,
    line_break
} t_mode_enum;

typedef enum e_sorting {
    unsorted,
    size,
    mod_time,
    chg_time,
    acc_time,
    crt_time,
    names
} t_sorting_enum;

typedef enum e_timetype {
    mod,
    chg,
    acc,
    crt
} t_time_enum;

typedef struct s_data {
    char *filename;
    char *full_filename;
    bool is_dir;

    // -l
    blkcnt_t blocks_count;
    char *permissions;
    bool has_acl;
    nlink_t links_count;
    char *owner;
    char *group;
    off_t file_size;
    char *symlink;
    mode_t mode;
    dev_t st_rdev;
    char *major;
    char *minor;

    // -@
    ssize_t xattr_value_length;
    char *xattr_text;

    // -t
    long last_modified;
    long last_modified_nsec;

    // -U
    long creation_time;
    long creation_time_nsec;

    // -u
    long last_access;
    long last_access_nsec;

    // -c
    long last_changed;
    long last_changed_nsec;

    ino_t inode;
} t_data;

typedef struct s_settings {
    t_mode_enum mode;
    t_sorting_enum sorting;
    t_time_enum time;
    bool has_output_format_flag;
    bool is_atty;
    bool has_many_file_arguments;
    bool not_found;
    bool is_first;
    bool many_lists;

    bool reverse; // -r
    bool format_size; // -h
    bool print_xattr; // -@
    bool print_xcols; // -x
    bool full_time; // -T
    bool omit_group; // -o
    bool colored; // -G
    bool omit_owner; // -g
    bool print_inode; // -i
    bool append_slash;// -p
    bool append_type_sign; // -F
    bool n; // -n
    bool a; // -a
    bool A; // -A
    bool R; // -R
} t_settings;

typedef struct s_max_len {
    int filenames;
    int links;
    int owners;
    int groups;
    int sizes;
    int xattrs_sizes;
    int inodes;
} t_max_len;

typedef struct s_colunms_info {
    t_max_len *max;
    int max_len;
    int list_size;
    int cols;
    int rows;
    int i;
    int j;
} t_columns_info;

typedef struct s_error {
    char *filename;
    int error;
} t_error;

// Functions
// Core
t_settings *mx_setup(char **flags);
void mx_read_data(t_settings *setup, char **files, char *f);
void mx_process_l(t_st st, t_data *data, t_settings *settings);
void mx_sort_data_list(t_list **data, t_settings *settings);
void mx_proccess_output(t_list **list, t_settings *settings);

// Errors
void mx_create_error(t_list **errlist, char *fname);
void mx_check_usage_error(char **flags, char **files);
void mx_print_uls_error(t_list *err_list);
void mx_print_notfound(t_list *err_list);
void mx_clear_list(t_list **list);

// Utils
char **mx_store_flags(int argc, char **argv);
char **mx_store_files(int argc, char **argv);
char *mx_check_flags(char **flags);
void mx_print_spaces(int count);
char mx_get_file_type(mode_t mode);
bool mx_search_strarr(char **strarr, char *str);
bool mx_check_chr_or_blk_device(t_list **list);
char *mx_convert_size(off_t st_size);
bool mx_has_output_format_flag(char **flags);
int mx_count_unique(char **arr, char *str);
bool mx_has_acl(char *dirname);
void mx_clear_tdata_list(t_list **list);
int mx_round_number(double g);
void mx_free_data(char **flags, t_settings *settings);

// Getters
t_max_len *mx_get_max_len_struct(t_list *list, t_settings *settings);
int mx_get_total(t_list *list);
char *mx_get_permissions(mode_t mode);
char *mx_get_xattr(char *dirname, ssize_t *length);
char *mx_get_group(gid_t st_gid, t_settings *settings);
char *mx_get_owner(uid_t st_uid, t_settings *settings);
char *mx_get_symlink(t_data * data);
char *mx_get_major(int st_rdev);
char *mx_get_minor(int st_rdev);
ushort mx_get_terminal_width(t_settings *settings);
t_columns_info *mx_get_columns_info(t_list **list, t_settings *settings,
                                    t_max_len *max);
char *mx_get_full_filename(char *dirpath, char *filename);
int mx_uls_h_get_pow(off_t st_size);

// Comparators
bool mx_filename_asc_cmp(void *data_1, void *data_2);
bool mx_filename_desc_cmp(void *data_1, void *data_2);
bool mx_last_modification_time_asc_cmp(void *data_1, void *data_2);
bool mx_last_modification_time_desc_cmp(void *data_1, void *data_2);
bool mx_size_asc_cmp(void *data_1, void *data_2);
bool mx_size_desc_cmp(void *data_1, void *data_2);
bool mx_last_changed_time_asc_cmp(void *data_1, void *data_2);
bool mx_last_changed_time_desc_cmp(void *data_1, void *data_2);
bool mx_creation_time_asc_cmp(void *data_1, void *data_2);
bool mx_creation_time_desc_cmp(void *data_1, void *data_2);
bool mx_last_access_time_asc_cmp(void *data_1, void *data_2);
bool mx_last_access_time_desc_cmp(void *data_1, void *data_2);

// Sortings
void mx_sort(t_list **list, bool (*cmp)(void *a, void *b));
void mx_sort_by_name(t_list **list, t_settings *settings);
void mx_sort_by_creation_time(t_list **list, t_settings *settings);
void mx_sort_by_last_access_time(t_list **list, t_settings *settings);
void mx_sort_by_last_modification_time(t_list **list, t_settings *settings);
void mx_sort_by_last_changed_time(t_list **list, t_settings *settings);
void mx_sort_by_size(t_list **list, t_settings *settings);
void mx_sort_errors(t_list **errors);

// Printing data
void mx_print_total(t_list *list);
void mx_print_filename_and_total(t_list *node, t_list *inner_node,
                                 t_settings *settings);
void mx_print_acl_xattr_or_nothing(t_data *data);
void mx_print_date(t_data *data, t_settings *settings);
void mx_print_size(t_data *data, t_max_len *max_len, bool is_device_met,
                   t_settings *settings);
void mx_print_symlink(t_data *data);
void mx_print_xattrs_text(t_data *data, t_settings *settings,
                          t_max_len *max_len);
void mx_print_filename(t_data *data, t_settings *settings);
void mx_print_colored(t_data *data);
void mx_print_inode(t_settings *settings, ino_t inode, t_max_len *max_len);
void mx_print_dir(char *dirname, t_settings *settings);
void mx_print_owner_group(t_settings *settings, t_data *data, t_max_len *len);
void mx_print_tabs(t_settings *settings, t_columns_info *info, t_data *prev);
void mx_print_columns_colored_spaces(t_settings *settings, t_data *prev,
                                     t_columns_info *info);

// Printing modes
// -l -g -o -n
void mx_print_long(t_list **list, t_settings *settings);
// -C
void mx_print_columns(t_list **list, t_settings *settings);
// -x
void mx_print_x_columns(t_list **list, t_settings *settings);
// -1
void mx_print_force(t_list **list, t_settings *settings);
// -m
void mx_print_stream(t_list **list, t_settings *settings);

#endif

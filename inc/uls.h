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
    char *filename;
    char *lm_time;
    long long file_size;
    unsigned int group_id;
    char *owner;
    unsigned short links_cout;
    char *permissions;
    char *extended_attrs;
    char *full_path;
    long long blocks_count;
    char *text_acl;
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
char *mx_get_permissions(unsigned short mode);
void mx_print_permissions(unsigned short mode);
bool mx_search_strarr(char **strarr, char *str);

#endif

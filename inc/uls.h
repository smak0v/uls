#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>

#include <uuid/uuid.h>

// Constants
#define ALLOWED_FLAGS "l"
// #define ALLOWED_FLAGS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"

// Structures
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

// Functions
char **mx_store_flags(int argc, char **argv);
char **mx_store_files(int argc, char **argv);
void mx_errors_handler(char **flags, char **files);
char *mx_check_flags(char **flags);
char *mx_format_time(char *lm_time);
void mx_print_spaces(int count);
char *mx_get_permissions(unsigned short mode);
void mx_print_permissions(unsigned short mode);

#endif

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

// #define ALLOWED_FLAGS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"
#define ALLOWED_FLAGS "l"
#define ILLEGAL_OPTION "uls: illegal option -- "
// #define USAGE_ERROR "usage: uls [-ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1] [file ...]\n"
#define USAGE_ERROR "usage: uls [-l] [file ...]\n"

char **mx_store_flags(int argc, char **argv);
char **mx_store_files(int argc, char **argv);
void mx_errors_handler(char **flags, char **files);
char *mx_check_flags(char **flags);

#endif

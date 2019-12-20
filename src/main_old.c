#include "uls.h"

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    
    mx_errors_handler(flags, files);

    // TODO Refactor:)
    acl_t acl = NULL;
    ssize_t xattr = 0;
    struct stat st;
    if (!(*files)) {
        DIR *dir = opendir(".");
        struct dirent *directory = NULL;
        while ((directory = readdir(dir)) != NULL) {
            if (directory->d_name[0] != '.') {
                acl = acl_get_file(directory->d_name, ACL_TYPE_EXTENDED);
                xattr = listxattr(directory->d_name, NULL, 0, XATTR_NOFOLLOW);
                if (xattr < 0)
                    xattr = 0;
                if (stat(directory->d_name, &st) == 0) {
                    mx_print_permissions(st.st_mode);
                    if (xattr > 0)
                        mx_printstr("@ ");
                    else if (acl)
                        mx_printstr("+ ");
                    else
                        mx_print_spaces(2);
                    mx_printint(st.st_nlink);
                    mx_print_spaces(1);
                    struct passwd *passwd_ptr1 = getpwuid(st.st_uid);
                    mx_printstr(passwd_ptr1->pw_name);
                    mx_print_spaces(2);
                    mx_printint(st.st_gid);
                    mx_print_spaces(2);
                    mx_printint(st.st_size);
                    mx_print_spaces(1);
                    char *lm_time = ctime(&st.st_mtimespec.tv_sec);
                    char *formated_lm_time = mx_format_time(lm_time);
                    mx_printstr(formated_lm_time);
                    mx_print_spaces(1);
                    mx_strdel(&formated_lm_time);
                }
                mx_printstr(directory->d_name);
                mx_printchar('\n');
                acl_free(acl);
            }
            
        }
        closedir(dir);
    }

    return 0;
}

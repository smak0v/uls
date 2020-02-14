#include "uls.h"

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = mx_setup(flags);
    int exit_code = 0;

    mx_check_usage_error(flags, files);
    mx_read_data(settings, files, ".");
    if (settings->not_found)
        exit_code = 1;
    mx_free_data(flags, settings);
    mx_del_strarr(&files);
    // system("leaks -q uls");
    return exit_code;
}

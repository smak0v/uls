#include "uls.h"

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = mx_setup(flags);
    t_list *errors = NULL;

    mx_check_usage_error(flags, files);
    mx_read_data(settings, files, ".");
    // mx_free_data(flags, settings);
    // mx_del_strarr(&files);
    if (errors)
        return 1;
    // system("leaks uls");
    return 0;
}



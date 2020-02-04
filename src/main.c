#include "uls.h"

static void free_data(char **flags, t_settings *settings) {
    mx_del_strarr(&flags);
    free(settings);
    settings = NULL;
}

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = NULL;
    t_list *data =  NULL;
    t_list *errors = NULL;

    settings = mx_setup(flags);
    mx_check_usage_error(flags, files);
    mx_read_data(&data, settings, files, ".");
    mx_print_errors(errors);
    mx_sort_and_output(&data, settings);
    free_data(flags, settings);
    if (errors)
        return 1;
    // system("leaks uls");
    return 0;
}

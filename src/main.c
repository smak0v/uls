#include "uls.h"

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = NULL;
    t_list *data =  NULL;
    t_list *errors = NULL;

    settings = mx_setup(flags);
    mx_check_usage_error(flags, files);
    errors = mx_read_data(flags, files, &data, ".");
    mx_print_errors(errors);
    mx_process_output(&data, settings, flags);

    // Leak cleaning
    mx_del_strarr(&flags);
    mx_del_strarr(&files);
    free(settings);
    settings = NULL;
    // TODO free(data)
    // system("leaks uls");
    return 0;
}

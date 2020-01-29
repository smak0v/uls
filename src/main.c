#include "uls.h"

static void free_data(char **flags, t_settings *settings);

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = NULL;
    t_list *data =  NULL;
    t_list *errors = NULL;
    int exit_code = 0;

    settings = mx_setup(flags);
    mx_check_usage_error(flags, files);
    mx_read_data(&data, settings, files, ".");
    //mx_print_errors(errors);
    mx_process_output(&data, settings, flags);
    if (errors)
        exit_code = 1;
    else
        exit_code = 0; 
    free_data(flags, settings);
    // system("leaks uls");
    return exit_code;
}

static void free_data(char **flags, t_settings *settings) {
    mx_del_strarr(&flags);
    free(settings->data);
    settings->data = NULL;
    free(settings);
    settings = NULL;
}

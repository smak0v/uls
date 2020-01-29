#include "uls.h"

static void free_data(char **flags, t_settings *settings);

void print_list(t_list **data) {
    t_list *outer_data = *data;
    t_list *inner_data = outer_data->data;

    while (outer_data) {
        inner_data = outer_data->data;
        mx_printstr_endl(((t_data *)inner_data->data)->filename);
        inner_data = inner_data->next;

        while (inner_data) {
            mx_printstr("  ");
            mx_printstr_endl(((t_data *)inner_data->data)->filename);
            mx_printstr("  ");
            mx_printstr_endl(((t_data *)inner_data->data)->permissions);
            mx_printchar('\n');
            inner_data = inner_data->next;
        }
        outer_data = outer_data->next;
    }
}

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
    print_list(&data);
    //mx_print_errors(errors);
    //mx_process_output(&data, settings, flags);
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

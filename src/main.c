#include "uls.h"

int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_settings *settings = NULL;
    t_list *data =  NULL;

    settings = mx_setup(flags);
    mx_errors_handler(flags, files);
    mx_read_data(flags, files, &data, ".");
    mx_process_output(&data, settings);
}

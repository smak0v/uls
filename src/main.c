#include "uls.h"

static void free_data(char **flags, t_settings *settings) {
    mx_del_strarr(&flags);
    free(settings);
    settings = NULL;
}

// static bool cmp(void *d_1, void *d_2) {
//     t_list *data_1 = (t_list *)d_1;
//     t_list *data_2 = (t_list *)d_2;

//     if (mx_strcmp(data_1->data, data_2->data) > 0)
//         return true;
//     return false;
// }

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
    mx_process_output(&data, settings, flags);

    // mx_push_back(&data, mx_strdup("dfsadfasd"));
    // mx_push_back(&data, mx_strdup("agDASDFGSA"));
    // mx_push_back(&data, mx_strdup("21312423"));
    // mx_push_back(&data, mx_strdup("dfsadGSFAGASFfasd"));
    // mx_push_back(&data, mx_strdup("FGD34QT"));
    // mx_push_back(&data, mx_strdup("ASGDASD"));
    // mx_push_back(&data, mx_strdup("dfsadfasd"));
    // mx_push_back(&data, mx_strdup("SADGASG"));
    // mx_push_back(&data, mx_strdup("dfsadfasd"));
    // mx_push_back(&data, mx_strdup("sfhgdfshsdf"));
    // mx_list_quicksort(&data, cmp);
    // t_list *l = data;
    // while (l) {
    //     mx_printstr_endl(l->data);
    //     l = l->next;
    // }

    free_data(flags, settings);
    if (errors)
        return 1;
    system("leaks uls");
    return 0;
}

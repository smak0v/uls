#include "uls.h"

void mx_free_data(char **flags, t_settings *settings) {
    mx_del_strarr(&flags);
    free(settings);
    settings = NULL;
}

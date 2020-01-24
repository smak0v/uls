#include "libmx.h"

char **mx_pop_string_array(char **arr, char *value) {
    int len = mx_strarr_len(arr);
    char **new_arr = NULL;
    int i = 0;
    int j = 0;

    if (len > 1) {
        new_arr = malloc(sizeof(char *) * len);
        while (arr[i]) {
            if (mx_strcmp(arr[i], value) != 0) {
                new_arr[j] = mx_strdup(arr[i]);
                j++;
            }
            i++;
        }
        new_arr[j] = NULL;
    }

    mx_del_strarr(&arr);
    return new_arr;
}

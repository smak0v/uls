#include "uls.h"
//MIGRATE TO MEMRCHR

char *mx_get_full_filename(char *dirpath, char *filename) {
    char *tmp = NULL;
    char *full_filename = NULL;

    if (dirpath[mx_strlen(dirpath) - 1] != '/') {
        tmp = mx_strjoin(dirpath, "/");
        full_filename = mx_strjoin(tmp, filename);
        mx_strdel(&tmp);
    }
    else
        full_filename = mx_strjoin(dirpath, filename);

    return full_filename;
}

static char *build_path(char ***strarr_ptr, int len, char *full_path) {
    char **strarr = *strarr_ptr;
    char *res = mx_strdup(strarr[0]);
    char *tmp = NULL;

    for (int i = 1; i < len - 1; i++) {
        tmp = mx_strjoin(res, "/");
        mx_strdel(&res);
        res = mx_strjoin(tmp, strarr[i]);
        mx_strdel(&tmp);
    }
    mx_del_strarr(&strarr);
    if (full_path[0] == '/') {
        tmp = mx_strjoin("/", res);
        mx_strdel(&res);
        return tmp;
    }
    return res;
}

char *mx_get_dirname(char *full_path) {
    char **strarr = NULL;
    int len;

    if (mx_get_char_index(full_path, '/') == -1)
        return mx_strdup(".");
    else {
        strarr = mx_strsplit(full_path, '/');
        len = mx_strarr_len(strarr);
        if (len == 1) {
            mx_del_strarr(&strarr);
            return mx_strdup("/");
        }
        return build_path(&strarr, len, full_path);
    }
}

char *mx_get_filename(char *full_path) {
    char **strarr = NULL;
    char *res = NULL;

    if (mx_get_char_index(full_path, '/') == -1)
        return mx_strdup(full_path);
    else {
        strarr = mx_strsplit(full_path, '/');
        res = mx_strdup(strarr[mx_strarr_len(strarr) - 1]);
        mx_del_strarr(&strarr);
        return res;
    }
}

char *mx_check_match(char **strarr, char *dirname, char *filename) {
    char *full_filename = NULL;

    if (mx_search_strarr(strarr, filename) == 1)
        return mx_strdup(filename);
    
    full_filename = mx_get_full_filename(dirname, filename);
    if (mx_search_strarr(strarr, full_filename) == 1)
        return full_filename;

    free(full_filename);
    return NULL;
}

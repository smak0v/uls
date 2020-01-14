#include "uls.h"

static void print_xattrs(t_data *data, t_max_len *max_len);
static void print_acl(t_data *data);

void mx_print_xattr_acl_text(t_data *data, t_settings *settings,
t_max_len *max_len) {
    if (settings->print_xattr && data->xattr_text)
        print_xattrs(data, max_len);
    if (settings->print_acl && data->acl_text)
        print_acl(data);
}

static void print_xattrs(t_data *data, t_max_len *max_len) {
    int max_num_len = mx_numlen(data->xattr_value_length);

    mx_printchar('\t');
    mx_printstr(data->xattr_text);
    mx_printchar('\t');
    mx_print_spaces(2);
    mx_print_spaces(max_num_len - max_len->xattrs_sizes);
    mx_printint_endl(data->xattr_value_length);
}

static void print_acl(t_data *data) {
    char **acl_arr = mx_strsplit(data->acl_text, '\n');
    char **tmp_arr_1 = NULL;
    char **tmp_arr_2 = NULL;

    for (int i = 1; i < mx_get_arr_length(acl_arr); i++) {
        tmp_arr_1 = mx_strsplit(acl_arr[i], ':');
        mx_print_spaces(1);
        mx_printint(i - 1);
        mx_printstr(": ");
        mx_printstr(tmp_arr_1[0]);
        mx_printchar(':');
        mx_printstr(tmp_arr_1[2]);
        mx_print_spaces(1);
        mx_printstr(tmp_arr_1[4]);
        mx_print_spaces(1);
        tmp_arr_2 = mx_strsplit(tmp_arr_1[5], ',');
        mx_bubble_sort(tmp_arr_2, mx_get_arr_length(tmp_arr_2));
        mx_print_strarr(tmp_arr_2, ",");
        //mx_printstr(tmp_arr_1[5]);
        mx_del_strarr(&tmp_arr_1);
        mx_del_strarr(&tmp_arr_2);
    }
    mx_del_strarr(&acl_arr);
    //mx_printstr(data->acl_text);
}

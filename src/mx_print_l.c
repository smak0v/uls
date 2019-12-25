#include "uls.h"

static void print_data(t_data *data);
static void print_size_or_major_minor(t_data *data);

void mx_print_l(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;

    mx_print_total(list);
    while (node) {
        inner_node = ((t_list *)node->data)->next;
        while (inner_node) {
            data = inner_node->data;
            print_data(data);
            inner_node = inner_node->next;
        }
        node = node->next;
    }
}

static void print_data(t_data *data) {
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_printstr(data->links_count);
    mx_print_spaces(1);
    mx_printstr(data->owner);
    mx_print_spaces(2);
    mx_printstr(data->group);
    mx_print_spaces(2);
    print_size_or_major_minor(data);
    mx_print_spaces(1);
    mx_print_date(data->last_modified);
    mx_print_spaces(1);
    mx_printstr(data->filename);
    if (data->symlink) {
        mx_printstr(" -> ");
        mx_printstr(data->symlink);
    }
    mx_printchar('\n');
}

static void print_size_or_major_minor(t_data *data) {
    if (S_ISCHR(data->mode) || S_ISBLK(data->mode)) {
        mx_printint(major(data->st_rdev));
        mx_print_spaces(3);
        int minor_num = minor(data->st_rdev);
        if (minor_num > 255) {
            mx_printstr(mx_nbr_to_hex(minor_num));
        }
        else
            mx_printint(minor_num);
    }
    else
        mx_printstr(data->file_size);
}

#include "uls.h"

static void print_data(t_data *data, t_max_len *max_len);
static void print_size_or_major_minor(t_data *data, t_max_len *max_len);
static void simple_output(t_list **list);
static void output_with_paths(t_list **list);

void mx_print_l(t_list **list) {
    mx_list_size(*list) == 1 ? simple_output(list) : output_with_paths(list);
}

static void simple_output(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        mx_print_total(inner_node);
        while (inner_node) {
            data = inner_node->data;
            print_data(data, max_len);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
    }
}

static void output_with_paths(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_data *data = NULL;
    t_max_len *max_len = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        mx_print_filename_and_total(node, inner_node);
        while (inner_node) {
            data = inner_node->data;
            print_data(data, max_len);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printstr("\n");
    }
}

static void print_data(t_data *data, t_max_len *max_len) {
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_print_spaces(max_len->links_max_len - mx_strlen(data->links_count));
    mx_printstr(data->links_count);
    mx_print_spaces(1);
    mx_printstr(data->owner);
    mx_print_spaces(max_len->owners_max_len - mx_strlen(data->owner) + 2);
    mx_printstr(data->group);
    mx_print_spaces(max_len->groups_max_len - mx_strlen(data->group) + 2);
    print_size_or_major_minor(data, max_len);
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

static void print_size_or_major_minor(t_data *data, t_max_len *max_len) {
    // TODO get major and minor + output it
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
    else {
        mx_print_spaces(max_len->sizes_max_len - mx_strlen(data->file_size));
        mx_printstr(data->file_size);
    }
}

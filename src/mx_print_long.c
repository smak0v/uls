#include "uls.h"

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met);
static void print_size(t_data *data, t_max_len *max_len, bool is_device_met);
static void simple_output(t_list **list);
static void output_with_paths(t_list **list);

void mx_print_long(t_list **list) {
    mx_list_size(*list) == 1 ? simple_output(list) : output_with_paths(list);
}

static void simple_output(t_list **list) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    bool is_device_met = false;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        mx_print_total(inner_node);
        is_device_met = mx_check_chr_or_blk_device(&inner_node);
        while (inner_node) {
            print_data(inner_node->data, max_len, is_device_met);
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
    t_max_len *max_len = NULL;
    bool is_device_met = false;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        mx_print_filename_and_total(node, inner_node);
        is_device_met = mx_check_chr_or_blk_device(&inner_node);
        while (inner_node) {
            print_data(inner_node->data, max_len, is_device_met);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printstr("\n");
    }
}

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met) {
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_print_spaces(max_len->links_max_len - mx_strlen(data->links_count));
    mx_printstr(data->links_count);
    mx_print_spaces(1);
    mx_printstr(data->owner);
    mx_print_spaces(max_len->owners_max_len - mx_strlen(data->owner) + 2);
    mx_printstr(data->group);
    mx_print_spaces(max_len->groups_max_len - mx_strlen(data->group) + 2);
    print_size(data, max_len, is_device_met);
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

static void print_size(t_data *data, t_max_len *max_len, bool is_device_met) {
    if (is_device_met)
        if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode)) {
            mx_print_spaces(3 - mx_strlen(data->major));
            mx_printstr(data->major);
            mx_printstr(", ");
            mx_print_spaces(3 - mx_strlen(data->minor));
            mx_printstr(data->minor);
            return;
        }
        else {
            mx_print_spaces(8 - mx_strlen(data->file_size));
            mx_printstr(data->file_size);
        }
    else {
        mx_print_spaces(max_len->sizes_max_len - mx_strlen(data->file_size));
        mx_printstr(data->file_size);
    }
}

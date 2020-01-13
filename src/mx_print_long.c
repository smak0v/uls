#include "uls.h"

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met,
t_settings *t_settings);
static void simple_output(t_list **list, t_settings *settings);
static void output_with_paths(t_list **list, t_settings *settings);

void mx_print_long(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && settings->not_found)
        simple_output(list, settings);
    else
        output_with_paths(list, settings);
}

static void simple_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *inner_node = NULL;
    t_max_len *max_len = NULL;
    bool is_device_met = false;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner_node = ((t_list *)node->data)->next;
        if (mx_list_size(inner_node))
            mx_print_total(inner_node);
        is_device_met = mx_check_chr_or_blk_device(&inner_node);
        while (inner_node) {
            print_data(inner_node->data, max_len, is_device_met, settings);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
    }
}

static void output_with_paths(t_list **list, t_settings *settings) {
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
            print_data(inner_node->data, max_len, is_device_met, settings);
            inner_node = inner_node->next;
        }
        free(max_len);
        max_len = NULL;
        node = node->next;
        if (node)
            mx_printstr("\n");
    }
}

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met,
t_settings *settings) {
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_print_spaces(max_len->links_max_len - mx_strlen(data->links_count));
    mx_printstr(data->links_count);
    mx_print_spaces(1);
    mx_printstr(data->owner);
    mx_print_spaces(max_len->owners_max_len - mx_strlen(data->owner) + 2);
    mx_printstr(data->group);
    mx_print_spaces(max_len->groups_max_len - mx_strlen(data->group));
    settings->format_size == 1 ? mx_print_spaces(3) : mx_print_spaces(2);
    mx_print_size(data, max_len, is_device_met, settings);
    mx_print_spaces(1);
    mx_print_date(data->last_modified);
    mx_print_spaces(1);
    mx_printstr(data->filename);
    mx_print_symlink(data);
    mx_printchar('\n');
    mx_print_xattr_acl_text(data, settings, max_len);
}

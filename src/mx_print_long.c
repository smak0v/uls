#include "uls.h"

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met,
                       t_settings *settings) {
    mx_print_inode(settings, data->inode, max_len);
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_print_spaces(max_len->links - mx_numlen(data->links_count));
    mx_printint(data->links_count);
    mx_print_spaces(1);
    mx_print_owner_group(settings, data, max_len);
    settings->format_size ? mx_print_spaces(3) : mx_print_spaces(2);
    mx_print_size(data, max_len, is_device_met, settings);
    mx_print_spaces(1);
    mx_print_date(data, settings);
    mx_print_spaces(1);
    mx_print_filename(data, settings);
    mx_print_symlink(data);
    mx_printchar('\n');
    mx_print_xattrs_text(data, settings, max_len);
}

static void print_list(t_list **node, t_max_len *max_len, bool is_device_met,
                       t_settings *settings) {
    t_list *inner_node = *node;

    while (inner_node) {
        print_data(inner_node->data, max_len, is_device_met, settings);
        inner_node = inner_node->next;
    }
}

static void simple_output(t_list **list, t_settings *s) {
    t_list *node = *list;
    t_list *inner = NULL;
    t_max_len *max_len = NULL;
    char *tmp = NULL;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner = ((t_list *)node->data)->next;
        tmp = ((t_data *)((t_list *)node->data)->data)->filename;
        if (mx_strcmp(tmp, FILES) != 0 && mx_list_size(inner))
            mx_print_total(inner);
        print_list(&inner, max_len, mx_check_chr_or_blk_device(&inner), s);
        free(max_len);
        max_len = NULL;
        node = node->next;
    }
}

static void output_with_paths(t_list **list, t_settings *s) {
    t_list *node = *list;
    t_list *inner = NULL;
    t_max_len *max_len = NULL;
    char *tmp = NULL;
    bool is_first = true;

    while (node) {
        max_len = mx_get_max_len_struct(node);
        inner = ((t_list *)node->data)->next;
        tmp = ((t_data *)((t_list *)node->data)->data)->filename;
        if (mx_strcmp(tmp, FILES) != 0)
            mx_print_filename_and_total(node, inner, is_first, s);
        is_first = false;
        print_list(&inner, max_len, mx_check_chr_or_blk_device(&inner), s);
        free(max_len);
        max_len = NULL;
        node = node->next;
        node ? mx_printstr("\n") : (void)0;
    }
}

void mx_print_long(t_list **list, t_settings *settings) {
    if (mx_list_size(*list) == 1  && !settings->not_found)
        simple_output(list, settings);
    else
        output_with_paths(list, settings);
}

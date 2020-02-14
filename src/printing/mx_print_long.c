#include "uls.h"

static void print_data(t_data *data, t_max_len *max_len, bool is_device_met,
                       t_settings *settings) {
    mx_print_inode(settings, data->inode, max_len);
    mx_printstr(data->permissions);
    mx_print_acl_xattr_or_nothing(data);
    mx_print_spaces(max_len->links - mx_numlen(data->links_count));
    mx_printint(data->links_count);
    if (!settings->omit_owner || !settings->omit_group)
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

static void long_output(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *next = node->next;
    t_max_len *max_len = mx_get_max_len_struct(node, settings);
    bool is_device_met = mx_check_chr_or_blk_device(&next);

    while (next) {
        print_data(next->data, max_len, is_device_met, settings);
        next = next->next;
    }
    free(max_len);
    max_len = NULL;
}

void mx_print_long(t_list **list, t_settings *settings) {
    t_list *node = *list;
    char *tmp = ((t_data *)node->data)->filename;

    mx_print_dir(tmp, settings);
    settings->is_first = false;
    if (mx_strcmp(tmp, FILES) && mx_list_size(node) > 1)
        mx_print_total(node->next);
    long_output(list, settings);
}

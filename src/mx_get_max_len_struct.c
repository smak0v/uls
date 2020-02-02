#include "uls.h"

t_max_len *mx_get_max_len_struct(t_list *list, t_settings *settings) {
    t_list *inner_node = ((t_list *)list->data)->next;
    t_max_len *max_len = NULL;

    if (settings->mode == table
        || settings->print_xattr
        || settings->print_inode) {
        max_len = malloc(sizeof(t_max_len));
        if (settings->mode == table) {
            max_len->links = mx_get_max_len_by_links(inner_node);
            max_len->owners = mx_get_max_len_by_owners(inner_node);
            max_len->groups = mx_get_max_len_by_groups(inner_node);
            max_len->sizes = mx_get_max_len_by_sizes(inner_node);
        }
        if (settings->print_xattr && settings->mode == table)
            max_len->xattrs_sizes = mx_get_max_len_by_xattr_size(inner_node);
        if (settings->print_inode)
            max_len->inodes = mx_get_max_len_by_inodes(inner_node);
    }
    return max_len;
}

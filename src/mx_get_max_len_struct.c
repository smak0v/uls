#include "uls.h"

t_max_len *mx_get_max_len_struct(t_list *list) {
    t_list *inner_node = ((t_list *)list->data)->next;
    t_max_len *max_len = malloc(sizeof(t_max_len));

    max_len->links = mx_get_max_len_by_links(inner_node);
    max_len->owners = mx_get_max_len_by_owners(inner_node);
    max_len->groups = mx_get_max_len_by_groups(inner_node);
    max_len->sizes = mx_get_max_len_by_sizes(inner_node);
    max_len->xattrs_sizes = mx_get_max_len_by_xattr_size(inner_node);
    max_len->inodes = mx_get_max_len_by_inodes(inner_node);
    return max_len;
}

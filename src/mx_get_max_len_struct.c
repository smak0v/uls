#include "uls.h"

static void fill_max_len(t_max_len **len, t_list *inner_node, t_settings *s) {
    t_list *node = inner_node;
    t_data *data = NULL;

    while (node) {
        data = node->data;
        if (s->mode == table) {
            (*len)->links = MX_MAX((*len)->links, 
                                   mx_numlen(data->links_count));
            (*len)->owners = MX_MAX((*len)->owners, mx_strlen(data->owner));
            (*len)->groups = MX_MAX((*len)->groups, mx_strlen(data->group));
            (*len)->sizes = MX_MAX((*len)->sizes, mx_numlen(data->file_size));
        }
        if (s->print_xattr && s->mode == table)
            (*len)->xattrs_sizes = MX_MAX((*len)->xattrs_sizes, 
                                          mx_numlen(data->xattr_value_length));
        if (s->print_inode)
            (*len)->inodes = MX_MAX((*len)->inodes, mx_unumlen(data->inode));
        node = node->next;
    }
}

t_max_len *mx_get_max_len_struct(t_list *list, t_settings *settings) {
    t_list *node = list;
    t_list *inner_node = ((t_list *)node->data)->next;
    t_max_len *max_len = NULL;

    if (settings->mode == table
        || settings->print_xattr
        || settings->print_inode) {
        max_len = mx_memalloc(sizeof(t_max_len));
        fill_max_len(&max_len, inner_node, settings);
    }
    return max_len;
}

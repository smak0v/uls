#include "uls.h"

static int get_max_len_by_links(t_list *list);
static int get_max_len_by_owners(t_list *list);
static int get_max_len_by_groups(t_list *list);
static int get_max_len_by_sizes(t_list *list);
static int get_max_len_by_xattr_size(t_list *list);

t_max_len *mx_get_max_len_struct(t_list *list) {
    t_list *inner_node = ((t_list *)list->data)->next;
    t_max_len *max_len = malloc(sizeof(t_max_len));

    max_len->links_max_len = get_max_len_by_links(inner_node);
    max_len->owners_max_len = get_max_len_by_owners(inner_node);
    max_len->groups_max_len = get_max_len_by_groups(inner_node);
    max_len->sizes_max_len = get_max_len_by_sizes(inner_node);
    max_len->xattrs_value_size_max_len = get_max_len_by_xattr_size(inner_node);
    return max_len;
}

static int get_max_len_by_links(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_strlen(data->links_count);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

static int get_max_len_by_owners(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_strlen(data->owner);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

static int get_max_len_by_groups(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_strlen(data->group);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

static int get_max_len_by_sizes(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_numlen(data->file_size);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

static int get_max_len_by_xattr_size(t_list *list) {
    t_list *node = list;
    t_data *data = NULL;
    int max_len = 0;
    int len = 0;

    while (node) {
        data = node->data;
        len = mx_numlen(data->xattr_value_length);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

#include "uls.h"

static void print(t_list *node, int *len, t_max_len *max_len,
                  t_settings *settings) {
    char *file = ((t_data *)(node->data))->filename;
    ushort width = mx_get_terminal_width(settings);

    if (settings->print_inode) {
        if (*len + mx_strlen(file) + 3 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        *len +=  max_len->inodes + mx_strlen(file) + 3;
    } else {
        if (*len + mx_strlen(file) + 2 >= width) {
            mx_printchar('\n');
            *len = 0;
        }
        *len += mx_strlen(file) + 2;
    }
    mx_print_inode(settings, ((t_data *)node->data)->inode, max_len);
    mx_print_filename((t_data *)node->data, settings);
    node->next ? mx_printstr(", ") : (void)0;
}

static void reset_values(int *len, t_max_len **max_len) {
    *len = 0;
    free(*max_len);
    *max_len = NULL;
}

void mx_print_stream(t_list **list, t_settings *settings) {
    t_list *node = *list;
    t_list *next = NULL;
    t_max_len *max_len = mx_get_max_len_struct(node, settings);
    char *tmp = ((t_data *)node->data)->filename;
    int len = 0;

    mx_print_dir(tmp, settings);
    settings->is_first = false;
    next = node->next;
    while (next) {
        print(next, &len, max_len, settings);
        next = next->next;
    }
    if (!mx_strcmp(tmp, FILES) && node->next)
        mx_printstr(", \n");
    else
        mx_printchar('\n');
    reset_values(&len, &max_len);
}

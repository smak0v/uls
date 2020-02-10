#include "uls.h"

static void print_new_line_and_reset(int *len) {
    mx_printchar('\n');
    *len = 0;
}

static int get_value(t_settings *settings, t_list *node) {
    t_data *data = (t_data *)node->data;
    int value = settings->print_inode ? 3 : 2;

    if (settings->append_slash && MX_IS_DIR(data->mode))
        ++value;
    else if (settings->append_type_sign) {
        if (MX_IS_DIR(data->mode))
            ++value;
        else if (MX_IS_REG(data->mode) && MX_IS_EXEC(data->mode))
            ++value;
        else if (MX_IS_LNK(data->mode))
            ++value;
        else if (MX_IS_SOCK(data->mode))
            ++value;
        else if (MX_IS_WHT(data->mode))
            ++value;
        else if (MX_IS_FIFO(data->mode))
            ++value;
    }
    return value;
}

static void print(t_list *node, int *len, t_max_len *max_len,
                  t_settings *settings) {
    char *file = ((t_data *)node->data)->filename;
    ushort width = mx_get_terminal_width(settings);
    int value = get_value(settings, node);

    if (!node->next) {
        if (*len + mx_strlen(file) >= width)
            print_new_line_and_reset(len);
    }
    else if (*len + mx_strlen(file) + value >= width)
        print_new_line_and_reset(len);
    if (settings->print_inode)
        *len += max_len->inodes + mx_strlen(file) + value;
     else
        *len += mx_strlen(file) + value;
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
    if (list && *list && (*list)->next) {
        if (!mx_strcmp(tmp, FILES) && node->next)
            mx_printstr(", \n");
        else
            mx_printchar('\n');
    }
    reset_values(&len, &max_len);
}

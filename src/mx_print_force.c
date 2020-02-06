#include "uls.h"

void mx_print_force(t_list **list, t_settings *settings, bool many_lists,
                    bool *is_first) {
    t_list *node = *list;
    t_list *next = NULL;
    t_data *data = NULL;
    t_max_len *max_len = mx_get_max_len_struct(node, settings);

    // if (many_lists)
    //     mx_print_dir(((t_data *)((t_list *)node->data)->data)->filename,
    //                  is_first, settings);
    next = node->next;
    while (next) {
        data = (t_data *)next->data;
        mx_print_inode(settings, data->inode, max_len);
        mx_print_filename(data, settings);
        mx_printchar('\n');
        next = next->next;
    }
    free(max_len);
    max_len = NULL; 

    many_lists = 1;
    *is_first = 1;
}

#include "uls.h"
#include <stdio.h>

// static void print_list(t_list **list) {
//     if (!list) {
//         mx_printstr("(null)\n");
//         return;
//     }
    
//     t_list *node = *list;
//     while (node) {
//         t_list *inner_node = (t_list *) node->data;
//         char *data1 = (char *) inner_node->data;
//         if (!data1)
//             mx_printstr("wtf\n");
//         else
//             printf("DIRNAME: %s\n", data1);
//         inner_node = inner_node->next;
    
//         while (inner_node) {
//             t_data *data = inner_node->data;

//             mx_printstr(data->filename);
//             mx_printchar('\n');
//             mx_printint(data->is_dir);
//             mx_printchar('\n');
//             mx_printstr(data->permissions);
//             mx_printchar('\n');
//             mx_printint(data->acl);
//             mx_printchar('\n');
//             mx_printint(data->xattr);
//             mx_printchar('\n');
//             mx_printint((int) data->links_count);
//             mx_printchar('\n');
//             mx_printstr(data->owner);
//             mx_printchar('\n');
//             mx_printstr(data->group);
//             mx_printchar('\n');
//             printf("%lld\n", data->file_size);
//             mx_printstr(data->last_modified);
//             mx_printchar('\n');
//             mx_printchar('\n');

//             inner_node = inner_node->next;
//         }

//         node = node->next;
//     }
// }


int main(int argc, char *argv[]) {
    char **flags = mx_store_flags(argc, argv);
    char **files = mx_store_files(argc, argv);
    t_list *data =  NULL;

    mx_errors_handler(flags, files);
    mx_read_data(flags, files, &data, ".");
    //mx_process_output(data, flags);
 
    // For long output
    mx_right_align_links(&data);
    mx_left_align_owner(&data);
    mx_left_align_group(&data);
    mx_right_align_size(&data);

    mx_print_l(&data);
    // if (data) {
    //     print_list(&data);
    // }
}



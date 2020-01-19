#include "uls.h"

void mx_print_inode(t_settings *settings, ino_t inode, t_max_len *max_len) {
    char *serial_number = NULL;

    if (settings->print_inode) {
        mx_print_spaces(max_len->inodes - mx_unumlen(inode));
        serial_number = mx_ulltoa(inode);
        mx_printstr(serial_number);
        mx_printchar(' ');
        mx_strdel(&serial_number);
    }
}

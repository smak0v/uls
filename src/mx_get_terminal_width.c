#include "uls.h"

ushort mx_get_terminal_width(t_settings *settings) {
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (settings->print_inode
        && !settings->is_atty
        && settings->mode == commas)
        return 90;
    if (!settings->is_atty)
        return 80;
    return w.ws_col;
}

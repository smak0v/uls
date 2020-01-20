#include "uls.h"

ushort mx_get_terminal_width(t_settings *settings) {
    struct winsize w;
    t_mode_enum mode;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (settings->print_inode
        && !isatty(1)
        && (int)(mode = commas) == settings->mode)
        return 90;
    if (!isatty(1))
        return 80;
    return w.ws_col;
}

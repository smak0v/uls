#include "uls.h"

unsigned short mx_get_terminal_width() {
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (!isatty(1))
        return 80;
    return w.ws_col;
}

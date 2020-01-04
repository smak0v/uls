#include "uls.h"

unsigned short mx_get_terminal_width() {
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

#include "terminal_size.h"

int get_terminal_size(TerminalSize *size) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return -1;  // Return -1 on error.
    }

    size->width = ws.ws_col;
    size->height = ws.ws_row;
    return 0;  // Success.
}
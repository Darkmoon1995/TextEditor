#include "input_control.h"
#include <termios.h>
#include <unistd.h>

static struct termios original_termios;

void disable_input() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &original_termios); // Save original settings
    new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // Apply changes
}

void enable_input() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios); // Restore settings
}

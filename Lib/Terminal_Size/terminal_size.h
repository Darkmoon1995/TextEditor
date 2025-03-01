#ifndef TERMINAL_SIZE_H
#define TERMINAL_SIZE_H

#include <sys/ioctl.h>
#include <unistd.h>

typedef struct {
    unsigned int width;
    unsigned int height;
} TerminalSize;

/**
 * Get the current size of the terminal.
 *
 * @param size A pointer to a TerminalSize structure to store the result.
 * @return 0 on success, -1 on failure.
 */
int get_terminal_size(TerminalSize *size);

#endif

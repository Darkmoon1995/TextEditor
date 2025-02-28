#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"

char *read_file_as_string(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    fclose(file);
    
    buffer[size] = '\0'; // Null-terminate

    // Remove trailing newline
    if (buffer[size - 1] == '\n') buffer[size - 1] = '\0';

    return buffer;
}


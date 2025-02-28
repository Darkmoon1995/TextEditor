#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <ctype.h>

// Converts all characters in a string to lowercase.
char* ToLowerChar(char *Text);

// Clears the contents of a string by setting each character to '\0'.
char* FreeFullString(char *Text);

#endif // STRING_UTILS_H

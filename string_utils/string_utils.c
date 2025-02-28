#include "string_utils.h"

char* ToLowerChar(char *Text) {
    for (int i = 0; Text[i]; i++) {
        Text[i] = tolower(Text[i]);
    }
    return Text;
}

char* FreeFullString(char *Text) {
    for (int i = 0; Text[i]; i++) {
        Text[i] = '\0';
    }
    return Text;
}

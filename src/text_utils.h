#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <stddef.h>

// Reverse a UTF-8 string for Hebrew RTL display
// Returns a newly allocated string that must be freed by the caller
char *text_reverse_hebrew(const char *input);

// Helper function to check if a character is Hebrew
int text_is_hebrew_char(unsigned char byte);

#endif // TEXT_UTILS_H
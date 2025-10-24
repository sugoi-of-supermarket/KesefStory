#include "text_utils.h"
#include <stdlib.h>
#include <string.h>

// Check if a byte sequence starts a Hebrew character (UTF-8)
// Hebrew Unicode range is U+0590 to U+05FF
// In UTF-8: 0xD6 0x90 to 0xD7 0xBF
int text_is_hebrew_char(unsigned char byte)
{
    return (byte == 0xD6 || byte == 0xD7);
}

char *text_reverse_hebrew(const char *input)
{
    if (!input) return NULL;

    size_t len = strlen(input);
    if (len == 0) return strdup("");

    // Allocate output buffer
    char *output = malloc(len + 1);
    if (!output) return NULL;

    // Simple character-by-character reversal for UTF-8
    // This works for Hebrew because each Hebrew character is 2 bytes in UTF-8
    const unsigned char *src = (const unsigned char *)input;
    unsigned char *dst = (unsigned char *)output;

    // Find the end position
    size_t pos = 0;
    size_t char_starts[512]; // Store start positions of characters
    size_t char_count = 0;

    // Parse UTF-8 characters and store their start positions
    while (pos < len && char_count < 512) {
        char_starts[char_count++] = pos;

        if (src[pos] < 0x80) {
            // ASCII character (1 byte)
            pos += 1;
        } else if ((src[pos] & 0xE0) == 0xC0) {
            // 2-byte UTF-8 character
            pos += 2;
        } else if ((src[pos] & 0xF0) == 0xE0) {
            // 3-byte UTF-8 character
            pos += 3;
        } else if ((src[pos] & 0xF8) == 0xF0) {
            // 4-byte UTF-8 character
            pos += 4;
        } else {
            // Invalid UTF-8, skip
            pos += 1;
        }
    }

    // Reverse the characters
    size_t out_pos = 0;
    for (size_t j = 0; j < char_count; j++) {
        size_t i = char_count - 1 - j;  // Reverse index
        size_t char_start = char_starts[i];
        size_t char_len;

        if (i == char_count - 1) {
            char_len = len - char_start;
        } else {
            char_len = char_starts[i + 1] - char_start;
        }

        // Copy the character
        memcpy(dst + out_pos, src + char_start, char_len);
        out_pos += char_len;
    }

    output[out_pos] = '\0';
    return output;
}

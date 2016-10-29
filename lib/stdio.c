#include <stdint.h>
#include <bkp/string.h>
#include <bkp/tty.h>

void term_printstring(const char* s) {
    int i;
    for (i = 0; i < strlen(s); i++) {
        term_printchar(s[i]);
    }
}

void term_print_binary(uint8_t n) {
    uint8_t mask = 128;
    while (mask > 0) {
        if (mask & n)
            term_printchar('1');
        else
            term_printchar('0');
        mask = mask/2;
    }
}


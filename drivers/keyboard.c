#include <stddef.h>
#include <stdint.h>
#include <bkp/tty.h>
#include <bkp/iomap.h>
#include <bkp/stdio.h>
#include <bkp/pic.h>

#define KB_CONTROL_REG 0x64
#define KB_ENCODE_REG 0x60
#define ENABLE 0xae

char scanset[256] = {0};

void initialize_scanset(void) {
    scanset[0x1e] = 'a';
    scanset[0x30] = 'b';
    scanset[0x2e] = 'c';
    scanset[0x20] = 'd';
    scanset[0x12] = 'e';
    scanset[0x21] = 'f';
    scanset[0x22] = 'g';
    scanset[0x23] = 'h';
    scanset[0x17] = 'i';
    scanset[0x24] = 'j';
    scanset[0x25] = 'k';
    scanset[0x26] = 'l';
    scanset[0x32] = 'm';
    scanset[0x31] = 'n';
    scanset[0x18] = 'o';
    scanset[0x19] = 'p';
    scanset[0x10] = 'q';
    scanset[0x13] = 'r';
    scanset[0x1f] = 's';
    scanset[0x14] = 't';
    scanset[0x16] = 'u';
    scanset[0x2f] = 'v';
    scanset[0x11] = 'w';
    scanset[0x2d] = 'x';
    scanset[0x15] = 'y';
    scanset[0x2c] = 'z';
    scanset[0x0b] = '0';
    scanset[0x02] = '1';
    scanset[0x03] = '2';
    scanset[0x04] = '3';
    scanset[0x05] = '4';
    scanset[0x06] = '5';
    scanset[0x07] = '6';
    scanset[0x08] = '7';
    scanset[0x09] = '8';
    scanset[0x0a] = '9';
    scanset[0x39] = ' ';
    scanset[0x1c] = '\n';
}

char key_pressed(uint8_t status) {
    return scanset[status];
}

void debug_status(void) {
    term_print_binary(inb(KB_CONTROL_REG));
}

void loop_handle(void) {
    int nchange = 0;
    uint8_t status = inb(KB_CONTROL_REG);
    uint8_t scancode = inb(KB_ENCODE_REG);
    uint8_t last_scancode = scancode;
    while (1) {
        status = inb(KB_CONTROL_REG);
        scancode = inb(KB_ENCODE_REG);
        if (scancode != last_scancode) {
            nchange++;
            if (nchange == 1) {
                term_printchar(key_pressed(scancode));
            } else if (nchange == 2) {
                nchange = 0;
            }
        }
        last_scancode = scancode;
        draw_term();
    }
}

void handle_keyboard_int(void) {
    uint8_t scancode = (uint8_t) inb(KB_ENCODE_REG);
    switch (scancode) {
        case 0x0e:
            term_backspace();
            break;
        default:
            term_printchar(key_pressed(scancode));
    }
    outb(PIC1_COMMAND,0x20);
    draw_term();
}

void initialize_keyboard(void) {
    initialize_scanset();
    outb(KB_CONTROL_REG,0xae);
}

void keyboard_debug(void) {
    initialize_scanset();
    term_printstring("\n");
    //uint8_t *keyboardstatus = (uint8_t*) 0x65;
    uint8_t keyboardstatus = (uint8_t) inb(0x64);
    uint8_t keystatus;
    loop_handle();
}


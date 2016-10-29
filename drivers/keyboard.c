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
    scanset[0x1e] = 'A';
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
    uint8_t scancode=inb(KB_ENCODE_REG);
    term_printchar(key_pressed(scancode));
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


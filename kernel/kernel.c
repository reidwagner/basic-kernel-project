#include <stddef.h>
#include <stdint.h>
#include <bkp/tty.h>
#include <bkp/iomap.h>
#include <bkp/stdio.h>
#include <bkp/keyboard.h>
#include <bkp/pic.h>

void main(void) {
    initialize_term();
    term_printstring("Kernel 0.1 booted succesfully.");
    inittests();
    //scroll_term(1);
    initialize_keyboard();
    term_printstring("\nInitializing keyboard interrupts.\n");
    initialize_idt();
    //keyboard_debug();
    term_printstring("Test keyboard input: ");
    draw_term();
}

void inittests(void) {
    term_printstring("\n\nRunning tests:");
    term_printstring("\nMultiline comment.");
    term_printstring("\nBinary print test: 254 == ");
    term_print_binary(254);
    term_printstring("b\n");
}
